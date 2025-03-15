#pragma once
#ifndef HTTPFETCHER_H
#define HTTPFETCHER_H

#include <wx/event.h>
#include <wx/string.h>
#include <thread>
#include <cpr/cpr.h>

// Define custom event type for fetching completion
wxDECLARE_EVENT(EVT_HTTP_FETCH_COMPLETE, wxThreadEvent);

class HttpFetcher {
public:
    HttpFetcher(wxEvtHandler* handler, const wxString& url);
    void Fetch();

private:
    void FetchData();
    wxEvtHandler* m_handler;
    wxString m_url;
};

#endif // HTTPFETCHER_H
