#include "HttpFetcher.h"

wxDEFINE_EVENT(EVT_HTTP_FETCH_COMPLETE, wxThreadEvent);

// Constructor
HttpFetcher::HttpFetcher(wxEvtHandler* handler, const wxString& url)
    : m_handler(handler), m_url(url) {}

void HttpFetcher::Fetch() {
    //creates a separate thread
    std::thread(&HttpFetcher::FetchData, this).detach();
}

void HttpFetcher::Destroy(){
    //mark as a thread to be killed
    dead = true;
}

void HttpFetcher::FetchData(){
    //make sync call (takes some time)
    cpr::Response response = cpr::Get(cpr::Url{m_url.ToStdString()});

    //send response back to the main thread (to be sure of order in execution)
    wxTheApp->CallAfter([this, response]() {
        //block and delete if dead
        if(dead){
            delete this;
            return;
        }

        //Emit Event
        auto event = new wxThreadEvent(EVT_HTTP_FETCH_COMPLETE);
        if(response.status_code == 200)
            event->SetPayload(response.text);
        else 
            event->SetPayload("");
        wxQueueEvent(m_handler, event);

        //delete
        delete this;
    });
}
