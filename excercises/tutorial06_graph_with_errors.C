/*
Purpose:
Plot measurements with horizontal and vertical uncertainties using
TGraphErrors. Error bars communicate the precision of every point.
*/

void tutorial06_graph_with_errors()
{
    std::ifstream input("tutorial06_data.txt");
    if (!input) {
        std::cerr << "Could not open tutorial06_data.txt" << std::endl;
        return;
    }

    // TGraphErrors stores x, y, and one uncertainty for each coordinate.
    TGraphErrors graph;

    double voltage = 0.0;
    double current = 0.0;
    double voltageError = 0.0;
    double currentError = 0.0;
    int point = 0;

    while (input >> voltage >> current >> voltageError >> currentError) {
        graph.SetPoint(point, voltage, current);
        graph.SetPointError(point, voltageError, currentError);
        ++point;
    }

    TCanvas canvas("canvas", "Graph with error bars", 800, 600);
    graph.SetTitle("Current-voltage measurement;Voltage [V];Current [mA]");
    graph.SetMarkerStyle(21);
    graph.SetMarkerColor(kRed + 1);
    graph.SetLineColor(kRed + 1);
    graph.Draw("AP");
    canvas.SetGrid();
    canvas.SaveAs("tutorial06_graph_with_errors.png");
}

/*
Questions to try:
1. Set all vertical errors to zero. What information disappears?
2. Increase one current uncertainty by a factor of ten. Which point looks least precise?
*/
