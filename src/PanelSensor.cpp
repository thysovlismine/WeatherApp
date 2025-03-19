#include "PanelSensor.h"
#include "JSONTools.h"
#include <wx/colour.h>
#include <wx/charts/wxlinechartdatasetoptions.h>
#include <limits>

//================================================================

PanelSensor::PanelSensor(Panel* origin, std::string _sensorId) : Panel(origin){
    //context
    sensorId = _sensorId;

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

    //window event
    mainWindow->Bind(wxEVT_SIZE, &PanelSensor::OnWindowResized, this);

    //Slider
    slider = new wxSlider(panel, wxID_ANY, (PanelSensor::sliderMaxValue + PanelSensor::sliderMinValue) / 2, PanelSensor::sliderMinValue, PanelSensor::sliderMaxValue, wxPoint(10, 10), wxSize(300, -1), wxSL_HORIZONTAL);
    slider->Bind(wxEVT_SLIDER, &PanelSensor::OnSliderChanged, this);

    //Button Back
    button_back = new wxButton(panel, wxID_ANY, "<--", wxPoint(10, 300), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelSensor::ButtonBack_OnButtonClick, this);

    //fetch data
    panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelSensor::OnDataFetched, this);
    FetchData();
}

PanelSensor::~PanelSensor(){
    //destroy objects by pointers
    slider->Destroy(); slider = nullptr;
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

void PanelSensor::OnWindowResized(wxSizeEvent& event){
    UpdateChart();
    mainWindow->Layout();
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
    LocalDB::LoadSensor(data, sensorId);

    //update main data
    {
        //check data params
        if(!data.contains("values"))
            return;
        if(!data["values"].is_array())
            return;

        //update slider
        slider->SetMin(0);
        slider->SetMax(data["values"].size());
        slider->SetValue(std::max(slider->GetMax() - PanelSensor::startingValueCount, slider->GetMin()));

        //make local stats
        size_t count = data["values"].size();
        chartValidCount = 0;
        chartSum = 0;
        chartMinIndex = 0;
        chartMaxIndex = 0;
        float y_min = std::numeric_limits<float>::min();
        float y_max = std::numeric_limits<float>::max();
        float y = 0;
        while(count--){
            //check value
            if(!JSON_isNumber(data["values"][count], "value"))
                continue;
            //parse
            y = JSON_ParseNumber(data["values"][count], "value");
            //sum
            chartSum += y;
            //min
            if(y < y_min){
                chartMinIndex = count + 1;
                y_min = y;
            }
            //max
            if(y > y_max){
                chartMaxIndex = count + 1;
                y_max = y;
            }
            //count
            chartValidCount++;
        }
    }

    //Update chart
    UpdateChart();
}

//================================================================

void PanelSensor::OnSliderChanged(wxCommandEvent& event){
    UpdateChart();
}

//================================================================

void PanelSensor::UpdateChartSize(){
    wxSize newSize = mainWindow->GetSize();
    newSize.SetWidth(newSize.GetWidth() - 60);
    newSize.SetHeight(newSize.GetHeight() - 60);
    chart->SetSize(newSize);
}

void PanelSensor::UpdateChart(){
    //check data params
    if(!data.contains("values"))
        return;
    if(!data["values"].is_array())
        return;

    //get range
    size_t count = data["values"].size();
    size_t i = count * ((float)(slider->GetValue() - slider->GetMin()) / (float)(slider->GetMax() - slider->GetMin()));

    //skip i=count
    if(i == count)
        return;

    //destroy chart
    if(chart != nullptr){
        chart->Destroy();
        chart = nullptr;
    }
    //init text calculation
    wxClientDC dc(panel); // Create a device context (DC)
    dc.SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    int labelTextWidth, labelTextHeight;

    //step size
    const int labelStepSize = ((mainWindow->GetSize().GetWidth() - 0) - 0) / (count - i);

    //distance
    int labelDistance = INT_MAX - labelStepSize;

    //make local stats
    chartLocalValidCount = 0;
    chartLocalSum = 0;
    chartLocalMinIndex = 0;
    chartLocalMaxIndex = 0;
    float y_min = std::numeric_limits<float>::min();
    float y_max = std::numeric_limits<float>::max();

    //add items
    wxVector<wxString> labels;
    wxVector<wxDouble> points;
    std::string x;
    float y;
    std::tm time;
    std::tm last_time = {};
    last_time.tm_sec = 0;    // Seconds [0, 60] (including leap second)
    last_time.tm_min = 0;    // Minutes [0, 59]
    last_time.tm_hour = 0;   // Hours [0, 23]
    last_time.tm_mday = 1;   // Day of month [1, 31]
    last_time.tm_mon = 0;    // Months since January [0, 11]
    last_time.tm_year = 0;   // Years since 1900 (year 1900)
    last_time.tm_wday = 0;   // Days since Sunday [0, 6] (computed automatically)
    last_time.tm_yday = 0;   // Days since Jan 1 [0, 365] (computed automatically)
    last_time.tm_isdst = -1; // Let the system determine daylight saving time;
    for(; i < count; i++){
        //get point
        x = JSON_ParseString(data["values"][i], "date");
        y = JSON_ParseNumber(data["values"][i], "value");
        
        //local stats
        if(JSON_isNumber(data["values"][i], "value")){
            //sum
            chartLocalSum += y;
            //min
            if(y < y_min){
                chartLocalMinIndex = i + 1;
                y_min = y;
            }
            //max
            if(y > y_max){
                chartLocalMaxIndex = i + 1;
                y_max = y;
            }
            //count
            chartLocalValidCount++;
        }
        
        //correct label name
        if(parseDateTime(x, time)){
            //check date
            if(
                time.tm_year == last_time.tm_year 
                &&
                time.tm_mon == last_time.tm_mon
                &&
                time.tm_mday == last_time.tm_mday
            )
                x = std::to_string(time.tm_hour) + ":" + std::to_string(time.tm_min)  + ":" + std::to_string(time.tm_sec);    
        }else{
            x = "?";
        }

        //get text size
        dc.GetTextExtent(wxString::FromUTF8(x), &labelTextWidth, &labelTextHeight);
        labelTextWidth /= 2;

        //make a step
        labelDistance += labelStepSize;        
        if(labelDistance > labelTextWidth){
            //take space and let the text be displayed
            labelDistance = -labelTextWidth;
        }
        else{
            //don't take space and skip rendering this text
            x = "";
        }

        //add points
        labels.push_back(x);
        points.push_back(y);

        //remember date
        if(x.length() > 0)
            last_time = time;
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
    
    //https://github.com/wxIshiko/wxCharts/issues/3
    wxLineChartOptions options;
    options.GetCommonOptions().SetShowTooltips(false);
    //options.GetGridOptions().SetShowGridLines(false);
    //
    chart = new wxLineChartCtrl(panel, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT, options, wxPoint(10, 30), wxSize(610, 410), wxBORDER_NONE);
    UpdateChartSize();
}

//================================================================

void PanelSensor::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}