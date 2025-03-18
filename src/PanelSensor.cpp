#include "PanelSensor.h"
#include <wx/colour.h>
#include <wx/charts/wxlinechartdatasetoptions.h>

//================================================================

PanelSensor::PanelSensor(Panel* origin, std::string _sensorId) : Panel(origin){
    //context
    sensorId = _sensorId;

    //List Sensors
    list = new wxListBox(panel, wxID_ANY, wxPoint(410, 30), wxSize(400, 250));
    
    

    // Create the data for the line chart widget
    /*
	wxVector<wxString> labels;
	labels.push_back("January");
	labels.push_back("February");
	labels.push_back("March");
	labels.push_back("April");
	labels.push_back("May");
	labels.push_back("June");

	labels.push_back("July1");
    labels.push_back("July2");
    labels.push_back("July3");
    labels.push_back("July4");
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
    points1.push_back(2);
    points1.push_back(3);
    points1.push_back(4);
    wxChartsDoubleDataset::ptr dataset1(new wxChartsDoubleDataset("My First Dataset", points1));
	chartData->AddDataset(dataset1);

    //chart
	chart = new wxLineChartCtrl(panel, wxID_ANY, chartData, wxCHARTSLINETYPE_STEPPED, wxPoint(10, 30), wxSize(400, 250), wxBORDER_NONE);
    */
   
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
    httpFetcher = new HttpFetcher(panel, "https://api.gios.gov.pl/pjp-api/rest/data/getData/" + sensorId);
    httpFetcher->Fetch();
}

void PanelSensor::OnDataFetched(wxThreadEvent& event){
    //unlock FetchParams function
    httpFetcher = nullptr;

    //get response
    std::string response = event.GetPayload<std::string>();

    //Update DB
    LocalDB::UpdateSensor(sensorId, response);

    //get data
    data = LocalDB::LoadSensor(sensorId);
    size_t count = data.size();

    //add items
    list->Clear();
    wxVector<wxString> labels;
    wxVector<wxDouble> points;
    for(size_t i = 0; i < count; i++){
        list->Append(std::to_string(data[i].value));
        labels.push_back(data[i].date);
        points.push_back(data[i].value);
        //if(i==10)
        //    break;
    }
    
    //labels
    wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared(labels);
    
    //points
    wxChartsDoubleDataset::ptr chartDataSet(new wxChartsDoubleDataset("My First Dataset", points));
    chartData->AddDataset(chartDataSet);
    
    //style
    // define pen color
    
    //wxChartsDatasetTheme *datasetTheme = new wxChartsDatasetTheme();
    //datasetTheme->SetLineChartDatasetOptions(wxLineChartDatasetOptions(wxColour("Red"), wxColour("Red"), wxColour("Red")));
    //wxChartsDefaultTheme->SetDatasetTheme(wxChartsDatasetId::CreateImplicitId(0),wxSharedPtr<wxChartsDatasetTheme>(datasetTheme));

    //Create the line chart widget from the constructed data
    if(chart == nullptr){
        //https://github.com/wxIshiko/wxCharts/issues/3
        wxLineChartOptions options;
        options.GetCommonOptions().SetShowTooltips(false);
        //options.GetGridOptions().SetShowGridLines(false);
        //
        chart = new wxLineChartCtrl(panel, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT, options, wxPoint(10, 30), wxSize(400, 250), wxBORDER_NONE);
        
        

    }
}

//================================================================

void PanelSensor::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}