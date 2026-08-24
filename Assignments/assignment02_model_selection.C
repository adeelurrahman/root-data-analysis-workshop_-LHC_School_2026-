/*
Purpose:
Choose a fit model for a Gaussian signal sitting on a background. The histogram
is supplied; the candidate functions and goodness-of-fit comparison are yours.
*/

#include <TCanvas.h>
#include <TH1D.h>
#include <TRandom3.h>

void assignment02_model_selection()
{
    TH1D histogram("histogram", "Signal with background;Measured value;Entries", 80, -5.0, 5.0);

    TRandom3 random(2718);

    // The first component is a narrow signal peak.
    for (int i = 0; i < 9000; ++i) {
        histogram.Fill(random.Gaus(0.7, 0.85));
    }

    // The second component is a flat background under the peak.
    for (int i = 0; i < 6000; ++i) {
        histogram.Fill(random.Uniform(-5.0, 5.0));
    }

    TCanvas canvas("canvas", "Model selection", 800, 600);
    histogram.SetMarkerStyle(20);
    histogram.Draw("E");
    canvas.SaveAs("assignment02_model_selection_start.png");

    /*
    Your work:
    1. Fit a Gaussian-only model.
    2. Fit a Gaussian plus a constant background.
    3. Fit a Gaussian plus a linear background.
    4. For each model, print chi-square, NDF, reduced chi-square, and probability.
    5. Compare  goodness of fit.
    6. Draw the preferred model.
    */
}
