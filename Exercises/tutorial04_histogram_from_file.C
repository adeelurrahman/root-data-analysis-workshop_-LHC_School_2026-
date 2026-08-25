/*
Purpose:
Read one measurement per line from tutorial04_data.txt and fill a histogram. This exercise
introduces file opening, input validation, and a safe stream-reading loop.
*/

void tutorial04_histogram_from_file()
{
    // ifstream opens a text file for reading.
    std::ifstream input("tutorial04_data.txt");
    if (!input) {
        std::cerr << "Could not open tutorial04_data.txt" << std::endl;
        return;
    }

    TH1D histogram("histogram", "Laboratory scores;Score;Students", 10, 0.0, 100.0);

    double score = 0.0;
    int valuesRead = 0;

    // The loop stops automatically when extraction fails or the file ends.
    while (input >> score) {
        histogram.Fill(score);
        ++valuesRead;
    }

    std::cout << "Read " << valuesRead << " scores" << std::endl;
    std::cout << "Histogram entries: " << histogram.GetEntries() << std::endl;

    TCanvas canvas("canvas", "Histogram from file", 800, 600);
    histogram.SetFillColor(kGreen - 7);
    histogram.Draw("hist");
    canvas.SaveAs("tutorial04_histogram_from_file.png");
}

/*
Questions to try:
1. What happens when a word is inserted halfway through tutorial04_data.txt?
2. How should the axis range change if scores above 100 are possible?
3. Compare 5, 10, and 20 bins. Which view best describes this small sample?
4. Use GetMean() and GetStdDev() to print two summary statistics.
*/
