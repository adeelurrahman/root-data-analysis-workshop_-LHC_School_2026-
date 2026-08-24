/*
Purpose:
Read the Gaussian sample produced in tutorial 7, fill a histogram, fit a
Gaussian function, and print the parameters and goodness-of-fit quantities.
*/

void tutorial08_fit_gaussian_data()
{
    std::ifstream input("tutorial07_gaussian_data.txt");
    if (!input) {
        std::cerr << "Gaussian data not found. Run tutorial 7 first." << std::endl;
        return;
    }

    TH1D histogram("histogram", "Gaussian sample;Measured value;Entries",
                   60, 0.0, 10.0);

    double value = 0.0;
    while (input >> value) {
        histogram.Fill(value);
    }

    // The formula "gaus" has parameters: normalization, mean, and sigma.
    TF1 gaussian("gaussian", "gaus", 1.0, 9.0);
    gaussian.SetLineColor(kRed + 1);
    gaussian.SetLineWidth(3);

    // &gaussian passes the address of the existing TF1 object to Fit(), allowing
    // ROOT to update that same function with the fitted parameter values.
    // R keeps the chosen range; S returns a TFitResultPtr with fit details.
    TFitResultPtr result = histogram.Fit(&gaussian, "RS");
    // TFitResultPtr is ROOT's pointer-like wrapper. Get() checks whether it holds
    // a valid result; later, -> accesses members of the result it points to.
    if (result.Get() == nullptr) {
        std::cerr << "The fit did not return a result." << std::endl;
        return;
    }

    const double chiSquare = result->Chi2();
    const int ndf = result->Ndf();
    const double reducedChiSquare = ndf > 0 ? chiSquare / ndf : 0.0;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Amplitude = " << gaussian.GetParameter(0)
              << " +/- " << gaussian.GetParError(0) << '\n';
    std::cout << "Mean      = " << gaussian.GetParameter(1)
              << " +/- " << gaussian.GetParError(1) << '\n';
    std::cout << "Sigma     = " << gaussian.GetParameter(2)
              << " +/- " << gaussian.GetParError(2) << '\n';
    std::cout << "Chi-square = " << chiSquare << '\n';
    std::cout << "NDF        = " << ndf << '\n';
    std::cout << "Reduced chi-square = " << reducedChiSquare << '\n';

    TCanvas canvas("canvas", "Gaussian fit", 800, 600);
    histogram.SetMarkerStyle(20);
    histogram.Draw("E");
    gaussian.Draw("same");
    canvas.SaveAs("tutorial08_gaussian_fit.png");
}

/*
Questions to try:
1. How does the reduced chi-square change with 20, 60, and 120 bins?
2. Restrict the fit range to [3, 7]. Are the fitted mean and sigma stable?
4. Add a few extreme values to the data file. Which parameter is affected most?
*/
