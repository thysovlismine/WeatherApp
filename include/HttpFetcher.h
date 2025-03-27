/**
 * @file HttpFetcher.h
 * @brief Defines the HttpFetcher class for performing HTTP GET requests asynchronously.
 *
 * This class is responsible for fetching data from a given URL using the cpr library.
 * The fetched data is then sent to the main thread via a custom wxWidgets event.
 */

 #pragma once
 #ifndef HTTPFETCHER_H
 #define HTTPFETCHER_H
 
 #include <wx/wx.h>
 #include <wx/event.h>
 #include <wx/string.h>
 #include <thread>
 #include <cpr/cpr.h>
 
 /**
  * @brief Custom event type for HTTP fetch completion.
  *
  * This event is emitted when an HTTP request is completed, carrying the response data.
  */
 wxDECLARE_EVENT(EVT_HTTP_FETCH_COMPLETE, wxThreadEvent);
 
 /**
  * @class HttpFetcher
  * @brief Handles asynchronous HTTP GET requests.
  *
  * HttpFetcher is responsible for fetching data from a given URL asynchronously using 
  * a separate thread. Once the request is completed, it sends an event back to the 
  * main thread.
  */
 class HttpFetcher {
 public:
     /**
      * @brief Constructor for HttpFetcher.
      * @param handler The wxEvtHandler that will receive the fetched data event.
      * @param url The URL to fetch data from.
      */
     HttpFetcher(wxEvtHandler* handler, const wxString& url);
 
     /**
      * @brief Initiates the asynchronous HTTP fetch operation.
      *
      * This method spawns a separate thread to perform the HTTP request.
      */
     void Fetch();
 
     /**
      * @brief Marks the instance for destruction.
      *
      * This method sets a flag indicating that the instance should be deleted once
      * the fetch operation completes.
      */
     void Destroy();
 
 private:
     /**
      * @brief Performs the actual HTTP GET request.
      *
      * This method runs in a separate thread, fetches data synchronously using cpr,
      * and then sends the result back to the main thread.
      */
     void FetchData();
 
     wxEvtHandler* m_handler; ///< Pointer to the event handler that receives the completion event.
     wxString m_url; ///< URL to be fetched.
     bool dead = false; ///< Flag indicating whether the instance should be deleted after execution.
 };
 
 #endif // HTTPFETCHER_H
 