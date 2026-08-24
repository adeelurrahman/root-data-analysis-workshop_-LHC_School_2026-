/*
Purpose:
Repeat the Gaussian fit and save the histogram, fitted function, and canvas in
a ROOT file. ROOT files preserve objects for later analysis, not just pictures.
*/

void tutorial09_save_fit_to_root_file()
{
    std::ifstream input("tutorial07_gaussian_data.txt");
    if (!input) {
        std::cerr << "Gaussian data not found. Run tutorial 7 first." << std::endl;
        return;
    }

    TH1D histogram("gaussian_histogram",
                   "Gaussian sample;Measured value;Entries", 60, 0.0, 10.0);

    double value = 0.0;
    while (input >> value) {
        histogram.Fill(value);
    }

    TF1 gaussian("gaussian_fit", "gaus", 1.0, 9.0);
    gaussian.SetLineColor(kRed + 1);
    TFitResultPtr result = histogram.Fit(&gaussian, "RS");
    if (result.Get() == nullptr || result->Status() != 0) {
        std::cerr << "Fit failed with status " << int(result) << std::endl;
        return;
    }

    std::cout << "Fitted mean  = " << gaussian.GetParameter(1) << std::endl;
    std::cout << "Fitted sigma = " << gaussian.GetParameter(2) << std::endl;
    std::cout << "Reduced chi-square = "
              << result->Chi2() / result->Ndf() << std::endl;

    TCanvas canvas("gaussian_canvas", "Gaussian fit", 800, 600);
    histogram.Draw("E");
    gaussian.Draw("same");
    canvas.SaveAs("tutorial09_gaussian_fit.png");

    // RECREATE makes a new ROOT file and replaces an older file with this name.
    TFile output("tutorial09_gaussian_fit.root", "RECREATE");
    if (output.IsZombie()) {
        std::cerr << "Could not create tutorial09_gaussian_fit.root" << std::endl;
        return;
    }

    // Write stores the current state of each object in the open ROOT file.
    histogram.Write();
    gaussian.Write();
    canvas.Write();
    output.Close();

    std::cout << "Saved gaussian_histogram, gaussian_fit, and gaussian_canvas"
              << " in tutorial09_gaussian_fit.root" << std::endl;
}

/*
Questions to try:
1. What happens if RECREATE is replaced with UPDATE and the macro is run twice?
2. Use rootls tutorial09_gaussian_fit.root. Which object names and classes are stored?
3. Is a PNG enough if another person wants to refit the data later?
*/
