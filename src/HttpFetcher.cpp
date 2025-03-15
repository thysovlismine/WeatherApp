#include "HttpFetcher.h"

wxDEFINE_EVENT(EVT_HTTP_FETCH_COMPLETE, wxThreadEvent);

HttpFetcher::HttpFetcher(wxEvtHandler* handler, const wxString& url)
    : m_handler(handler), m_url(url) {}

void HttpFetcher::Fetch() {
    // Run the fetch operation in a separate thread
    std::thread(&HttpFetcher::FetchData, this).detach();
}

void HttpFetcher::FetchData() {
    // Perform HTTP request using cpr
    cpr::Response response = cpr::Get(cpr::Url{m_url.ToStdString()});
    
    // Create event
    wxThreadEvent* event = new wxThreadEvent(EVT_HTTP_FETCH_COMPLETE);

    // Check if request was successful
    if (response.status_code == 200) {
        event->SetPayload(response.text);
    } else {
        event->SetPayload("");  // Send empty string on failure
    }

    // Send data back to the main thread
    wxQueueEvent(m_handler, event);

    //delete this object
    delete this;
}
