#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <cmath>

class ChartPanel : public wxPanel {
public:
    ChartPanel(wxFrame* parent) : wxPanel(parent) {
        SetBackgroundStyle(wxBG_STYLE_PAINT);  // Required for wxAutoBufferedPaintDC
        Bind(wxEVT_PAINT, &ChartPanel::OnPaint, this);
    }

private:
    void OnPaint(wxPaintEvent& event) {
        wxAutoBufferedPaintDC dc(this);
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();

        // Chart parameters
        int width, height;
        GetSize(&width, &height);
        int midX = width / 2, midY = height / 2;
        int scaleX = 30, scaleY = 50;

        // Draw axes
        dc.SetPen(*wxBLACK_PEN);
        dc.DrawLine(0, midY, width, midY);  // X-axis
        dc.DrawLine(midX, 0, midX, height); // Y-axis

        // Draw sine wave
        dc.SetPen(*wxBLUE_PEN);
        for (int x = -midX; x < midX; x++) {
            int y = std::sin(x / 30.0) * scaleY;  // Sine wave formula
            dc.DrawPoint(midX + x, midY - y);
        }
    }
};


class ChartFrame : public wxFrame {
public:
    ChartFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets Chart", wxDefaultPosition, wxSize(600, 400)) {
        new ChartPanel(this);
    }
};

class ChartApp : public wxApp {
public:
    bool OnInit() override {
        ChartFrame* frame = new ChartFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(ChartApp);
