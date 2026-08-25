/*
Purpose:
Create and draw a first ROOT histogram. The histogram records many uniform
random values and shows how entries are grouped into bins.
*/

void tutorial02_first_histogram()
{
    // TH1D is a one-dimensional histogram whose bin contents are stored as doubles.
    // Constructor convention:
    // TH1D variable("ROOT name", "title;x-axis title;y-axis title",
    //                number of bins, lower edge, upper edge);
    // This divides [0, 1] into 50 equal bins, each 0.02 units wide.
    TH1D histogram("histogram", "Uniform random numbers;Random value;Entries",
                   50, 0.0, 1.0);

    TRandom random(42);
    const int numberOfEntries = 10000;

    for (int i = 0; i < numberOfEntries; ++i) {
        // Fill finds the correct x-axis bin and increments its content.
        histogram.Fill(random.Rndm());
    }

    // TCanvas variable("ROOT name", "window title", width, height) creates the
    // drawing surface. The width and height are measured in pixels.
    TCanvas canvas("canvas", "First histogram", 800, 600);
    histogram.SetFillColor(kAzure - 9);
    histogram.SetLineColor(kAzure + 2);
    histogram.Draw("hist");

    canvas.SaveAs("tutorial02_first_histogram.png");
}

/*
Questions to try:
1. What happens to the fluctuations when the binning changes from 50 bins to 10?
2. What happens when the histogram has 100 bins but only 100 entries?
3. Change the range from [0, 1] to [0.2, 0.8]. Where do the other entries go?
4. Replace Rndm() with Gaus(0.5, 0.1). How does the shape change?
*/
