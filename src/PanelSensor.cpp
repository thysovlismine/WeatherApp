#include "PanelSensor.h"

//================================================================

PanelSensor::PanelSensor(Panel* origin, int _sensorId) : Panel(origin){
    //context
    sensorId = _sensorId;

    //List Sensors
    list = new wxListBox(panel, wxID_ANY, wxPoint(410, 30), wxSize(400, 250));
    
    //chart
	//chart = new wxLineChartCtrl(panel, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT, wxPoint(10, 30), wxSize(400, 250), wxBORDER_NONE);

    // Create the legend widget (optional)
	//wxChartsLegendData legendData(chartData->GetDatasets());
	//wxChartsLegendCtrl* legendCtrl = new wxChartsLegendCtrl(panel, wxID_ANY, legendData, wxPoint(0, 0), wxSize(100, 100), wxBORDER_NONE);

    // Set up the sizer for the panel
	//wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	//panelSizer->Add(lineChartCtrl, 1, wxEXPAND);
	//panelSizer->Add(legendCtrl, 1, wxEXPAND);
	//panel->SetSizer(panelSizer);





    //Button Back
    button_back = new wxButton(panel, wxID_ANY, "<--", wxPoint(10, 300), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelSensor::ButtonBack_OnButtonClick, this);

    //fetch data
    panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelSensor::OnDataFetched, this);
    FetchData();
}

PanelSensor::~PanelSensor(){
    //destroy objects by pointers
    list->Destroy(); list = nullptr;
    button_back->Destroy(); button_back = nullptr;
    if(chart != nullptr){
        chart->Destroy();
        chart = nullptr;
    }
    //Destroy HttpFetcher
    if(httpFetcher != nullptr){
        httpFetcher->Destroy();
        httpFetcher = nullptr;
    }
}

//================================================================

void PanelSensor::FetchData(){
    //block if already called
    if(httpFetcher != nullptr)
        return;

    //fetch data
    httpFetcher = new HttpFetcher(panel, "https://api.gios.gov.pl/pjp-api/rest/data/getData/" + std::to_string(sensorId));
    httpFetcher->Fetch();
}

void PanelSensor::OnDataFetched(wxThreadEvent& event){
    //unlock FetchParams function
    httpFetcher = nullptr;

    //get response
    std::string response = event.GetPayload<std::string>();
    wxMessageBox(response);

    //parse json
    try{
        nlohmann::json responseJSON = nlohmann::json::parse(response);
        
        // Create the data for the line chart widget
        //wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared(labels);

        // Add the first dataset
        //wxVector<wxDouble> points;
        //wxChartsDoubleDataset::ptr dataset1(new wxChartsDoubleDataset("My First Dataset", points));

        list->Append("start");
        //add items
        //wxChartData seriesData;
        wxVector<wxString> labels;
        wxVector<wxDouble> points;
        if(responseJSON.contains("values")){
            wxMessageBox("yes");
            for (const auto& item : responseJSON["values"]){
                if (item.contains("date")
                    && item.contains("value")
                ){
                    list->Append(wxString::FromUTF8( std::to_string((item["value"]).get<float>())));
                    labels.push_back(item["date"].get<std::string>());
                    points.push_back(item["value"].get<float>());
                    //list->Append("gag");
                }
                else{
                    list->Append("gag");
                }
            }
        }
        
        
        //labels
        wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared(labels);
        
        //points
        wxChartsDoubleDataset::ptr chartDataSet(new wxChartsDoubleDataset("My First Dataset", points));
        chartData->AddDataset(chartDataSet);

        // Create the line chart widget from the constructed data
        if(chart == nullptr){
            chart = new wxLineChartCtrl(panel, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT, wxPoint(10, 30), wxSize(400, 250), wxBORDER_NONE);
        }
    }
    catch(const std::exception&){
        ;
    }
}

//================================================================

void PanelSensor::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}