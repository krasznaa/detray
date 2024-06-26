# Detray library, part of the ACTS project (R&D line)
#
# (c) 2023 CERN for the benefit of the ACTS project
#
# Mozilla Public License Version 2.0

# detray includes
from validation import plot_material_scan as mat_plotter
from validation import plt_factory

# python includes
import argparse
import logging
import pandas as pd
import os
import sys
from datetime import datetime


def __main__():

#----------------------------------------------------------------arg parsing

    parser = argparse.ArgumentParser(description = "Detray Material Validation")
    parser.add_argument("--debug", "-d",
                        help=("Enables debug output"), 
                        action="store_true")
    parser.add_argument("--logfile",
                        help=("Write log in file"), 
                        default = "", type=str)
    parser.add_argument("--input", "-i",
                        help=("Input material scan data file."),
                        default = "", type=str)
    parser.add_argument("--outdir", "-o",
                        help=("Output directory for plots."),
                        default = "./material_plots/", type=str)
    parser.add_argument("--output_format", "-of",
                        help=("Format of the plot files (svg|png|pdf)."),
                        default = "png", type=str)

    args = parser.parse_args()

#---------------------------------------------------------------------config

    # Check output path
    if not os.path.isdir(args.outdir):
        os.mkdir(args.outdir, 0o755)
    outdir = args.outdir

    # Set log level
    logLevel = logging.INFO
    if args.debug:
        logLevel = logging.DEBUG

    # Check logfile path
    if args.logfile != "":
        logDirName  = os.path.dirname(args.logfile)

        if logDirName != "" and not os.path.isdir(logDirName):
            os.mkdir(logDirName, 0o755)

        if not os.path.isfile(args.logfile):
            with open(args.logfile, 'x'): pass

        # Write log in logfile
        logging.basicConfig(filename=args.logfile, 
                            format=("%(levelname)s (%(module)s):"
                                    " %(message)s"), level=logLevel)
    else:
        # Write log to terminal
        logging.basicConfig(format=("%(levelname)s (%(module)s):"
                                    " %(message)s"), level=logLevel)

    logging.info("\n--------------------------------------------------------\n"
                 "Running material validation "+\
                 str(datetime.now().strftime("%d/%m/%Y %H:%M"))+\
                 "\n--------------------------------------------------------\n")

    # Check input data files from material scan
    if args.input == "":
        logging.error(f"Please specify an input data file!")
        sys.exit(1)

    if not os.path.isfile(args.input):
        logging.error(f"Data file does not exist! ({args.input})")
        sys.exit(1)

    if not args.output_format in ["svg", "png", "pdf"]:
        logging.error(f"Unknown output file format: {args.output_format}")
        sys.exit(1)

    mat_scan_file = args.input
    out_format = args.output_format

#----------------------------------------------------------------prepare data

    # Get detector name
    detector_name = mat_scan_file.removeprefix('material_scan_')
    detector_name = detector_name.removesuffix('.csv')
    detector_name = detector_name.replace('_', ' ')

    df = pd.read_csv(mat_scan_file)

    plot_factory = plt_factory(outdir + "material_", logging)

#------------------------------------------------------------------------run

    # The histograms are not re-weighted (if the rays are not evenly distributed
    # the material in some bins might be artificially high)!
    mat_plotter.X0_vs_eta_phi(df, detector_name, plot_factory, out_format)
    mat_plotter.L0_vs_eta_phi(df, detector_name, plot_factory, out_format)
    mat_plotter.X0_vs_eta(df, detector_name, plot_factory, out_format)
    mat_plotter.L0_vs_eta(df, detector_name, plot_factory, out_format)

#-------------------------------------------------------------------------------

if __name__ == "__main__":
    __main__()

#------------------------------------------------------------------------------- 
