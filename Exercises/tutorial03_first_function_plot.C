/*
Purpose:
Plot an analytic function with TF1 and learn how a function range, parameters,
axis labels, and line style are set in ROOT.
*/

void tutorial03_first_function_plot()
{
    // TF1 variable("ROOT name", "formula", lower x, upper x) describes a
    // one-dimensional function. Numbered placeholders such as [0] and [1]
    // represent parameters whose values can be changed without rewriting the formula.
    TF1 dampedWave("dampedWave", "[0]*sin(x)*exp(-[1]*x)",
                   0.0, 4.0 * TMath::Pi());

    // Parameters [0] and [1] are the amplitude and damping coefficient.
    dampedWave.SetParameter(0, 1.0);
    dampedWave.SetParameter(1, 0.15);
    dampedWave.SetTitle("Damped sine wave;x;f(x)");
    dampedWave.SetLineColor(kBlue + 1);
    dampedWave.SetLineWidth(3);

    TCanvas canvas("canvas", "First function plot", 800, 600);
    dampedWave.Draw();
    canvas.SetGrid();
    canvas.SaveAs("tutorial03_first_function_plot.png");
}

/*
Questions to try:
1. Which part of the curve changes when parameter [0] is doubled?
2. What happens when the damping coefficient [1] is set to zero?
3. Extend the x range to 10*pi. Does the vertical scale remain useful?
*/
