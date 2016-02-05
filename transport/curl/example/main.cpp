#include <iostream>
#include <getopt.h>
#include "libgai/tracker.h"
#include "libgai/hit.h"
#include "libgai/curl/transport.h"



class ExampleTracker
{
public:
    ExampleTracker(const std::string& tracking_id,
                   const std::string& client_id)
        : tracker(NULL)
    {
        tracker = gai_tracker_new(
            tracking_id.c_str(),
            client_id.c_str(),
            gai_curl_transport_new());
    }

    ~ExampleTracker()
    {
        gai_tracker_free(tracker);
    }

    bool send_hit(struct gai_hit* hit)
    {
        return (gai_send_hit(tracker, hit) == 0);
    }

    void set_server(const std::string& server)
    {
        gai_tracker_set_server(tracker, server.c_str());
    }

private:
    struct gai_tracker* tracker;
};



struct gai_hit* build_hit(const std::string& type)
{
    gai_hit_type hit_type;
    if (type == "pageview") {
        hit_type = GAI_HIT_PAGEVIEW;
    } else if (type == "screenview") {
        hit_type = GAI_HIT_SCREENVIEW;
    } else if (type == "event") {
        hit_type = GAI_HIT_EVENT;
    } else if (type == "transaction") {
        hit_type = GAI_HIT_TRANSACTION;
    } else if (type == "item") {
        hit_type = GAI_HIT_ITEM;
    } else if (type == "social") {
        hit_type = GAI_HIT_SOCIAL;
    } else if (type == "exception") {
        hit_type = GAI_HIT_EXCEPTION;
    } else if (type == "timing") {
        hit_type = GAI_HIT_TIMING;
    } else {
        std::cerr << "Invalid hit type: " << type << std::endl;
        return NULL;
    }
    return gai_hit_new(hit_type);
}



void parse_hit_params(struct gai_hit* hit, int argc, char** argv)
{
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        std::size_t pos = arg.find("=");
        std::string param_name = arg.substr(0, pos);
        std::string param_value = arg.substr(pos+1);
        gai_hit_set_parameter(param_name.c_str(), param_value.c_str(), hit);
    }
}



void usage()
{
    std::cout << "Usage: gai_example";
    std::cout << " --tracking-id=<TRACKING_ID>";
    std::cout << " --client-id=<CLIENT_ID>";
    std::cout << " <HIT_TYPE>";
    std::cout << " [PARAM]=[VALUE] ...";
    std::cout << std::endl;
    std::cout << "Hit types: pageview, screenview, event, transaction, item,";
    std::cout <<            "social, exception, timing" << std::endl;
}



int main(int argc, char** argv)
{
    // Parse the command line flags
    static struct option longopts[] = {
        {"tracking-id", required_argument, NULL, 't'},
        {"client-id", required_argument, NULL, 'c'},
        {"server", required_argument, NULL, 's'},
        {"hit-type", required_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    std::string tracking_id;
    std::string client_id;
    std::string server;
    std::string hit_type;
    int ch;
    while ((ch = getopt_long(argc, argv, "t:c:s:h:", longopts, NULL)) != -1) {
        switch (ch) {
            case 't': tracking_id = optarg; break;
            case 'c': client_id = optarg; break;
            case 's': server = optarg; break;
            case 'h': hit_type = optarg; break;
            default: usage(); break;
        }
    }
    argc -= optind;
    argv += optind;

    // Validate the tracking and client IDs
    if (tracking_id.empty() || client_id.empty()) {
        std::cerr << "Error, specify tracking and client ID" << std::endl;
        usage();
        return 1;
    }

    // Validate the hit-type and build the hit
    if (hit_type.empty()) {
        std::cerr << "Error, specify the hit type" << std::endl;
        usage();
        return 1;
    }
    struct gai_hit* hit = build_hit(hit_type);
    if (hit == NULL) {
        usage();
        return 1;
    }
    parse_hit_params(hit, argc, argv);

    // Build and configure the tracker
    ExampleTracker tracker(tracking_id, client_id);
    if (!server.empty()) {
        tracker.set_server(server);
    }

    // Send the hit
    if (tracker.send_hit(hit)) {
        std::cout << "Hit was sent successfully" << std::endl;
        return 0;
    }

    std::cerr << "Hit failed to send" << std::endl;
    return 1;
}
