/*
Purpose:
Investigate how histogram binning changes the presentation of one fixed data
sample. Complete the marked section and support the final bin choice with data.
*/

void assignment01_binning_study()
{
    TRandom3 random(31415);

    TH1D reference("reference", "Reference binning;Measured value;Entries",
                   50, -5.0, 5.0);

    for (int i = 0; i < 3000; ++i) {
        reference.Fill(random.Gaus(0.4, 1.1));
    }

    TCanvas canvas("canvas", "Binning study", 800, 600);
    reference.Draw("E");
    canvas.SaveAs("assignment01_binning_study_start.png");

    /*
    Your work:
    1. Fill histograms with 10, 25, 50, and 100 bins using the same events.
       Do not generate a different random sample for each histogram.
    2. Draw the four histograms on a divided canvas.
    3. Fit each histogram with a Gaussian over the same range.
    4. Print mean, sigma, their uncertainties, and reduced chi-square.
    5. Choose a binning for reporting this measurement and justify it.
    */
}
