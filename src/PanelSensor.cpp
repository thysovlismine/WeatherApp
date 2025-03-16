#include "PanelSensor.h"

//================================================================

PanelSensor::PanelSensor(Panel* origin, int _sensorId) : Panel(origin){
    //context
    sensorId = _sensorId;

    //List Sensors
    //list = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(400, 250));
    
    //chart



    // Create the data for the line chart widget
	wxVector<wxString> labels;
	labels.push_back("January");
	labels.push_back("February");
	labels.push_back("March");
	labels.push_back("April");
	labels.push_back("May");
	labels.push_back("June");
	labels.push_back("July");
    wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared(labels);

    // Add the first dataset
	wxVector<wxDouble> points1;
	points1.push_back(3);
	points1.push_back(-2.5);
	points1.push_back(-1.2);
	points1.push_back(3);
	points1.push_back(6);
	points1.push_back(5);
	points1.push_back(1);
    wxChartsDoubleDataset::ptr dataset1(new wxChartsDoubleDataset("My First Dataset", points1));
	chartData->AddDataset(dataset1);

    // Add the second dataset
	wxVector<wxDouble> points2;
	points2.push_back(1);
	points2.push_back(-1.33);
	points2.push_back(2.5);
	points2.push_back(7);
	points2.push_back(3);
	points2.push_back(-1.8);
	points2.push_back(0.4);
    wxChartsDoubleDataset::ptr dataset2(new wxChartsDoubleDataset("My Second Dataset", points2));
	chartData->AddDataset(dataset2);

    // Create the line chart widget from the constructed data
	wxLineChartCtrl* lineChartCtrl = new wxLineChartCtrl(panel, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT, wxPoint(10, 30), wxSize(400, 250), wxBORDER_NONE);

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
    //panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelSensor::OnDataFetched, this);
    //FetchData();
}

PanelSensor::~PanelSensor(){
    //destroy objects by pointers
    list->Destroy(); list = nullptr;
    button_back->Destroy(); button_back = nullptr;
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

    //parse json
    try{
        nlohmann::json responseJSON = nlohmann::json::parse(response);
        

        list->Append("start");
        //add items
        //wxChartData seriesData;
        int i = 0;
        list->Clear();
        if(responseJSON.contains("values"))
            for (const auto& item : responseJSON["values"])
                if (item.contains("date")
                    && item.contains("value")
                ){
                    //seriesData.AddDataPoint(i++, item["value"].get<float>());
                    list->Append("gag");
                    list->Append(wxString::FromUTF8( std::to_string((item["value"]).get<float>()) ));
                }
                else{
                    list->Append("gag");
                }
        
        //update chart
        //wxChartLineSeries* series = new wxChartLineSeries(seriesData);
        //chart->AddSeries(series);
        //chart->Update();

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