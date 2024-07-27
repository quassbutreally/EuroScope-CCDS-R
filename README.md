# Welcome to CCDS-R for EuroScope

![Some Features of CCDS-R](https://github.com/user-attachments/assets/d7c9b65b-9120-4ef5-9b6f-bc03c8fd86ed "Some features of CCDS-R")

CCDS-R for EuroScope intends to bring a representation of the real-world CCDS-R system to EuroScope, primarily for VATSIM UK users, for a more authentic controlling experience. Some features include:

- Specific pre-determined code-callsign conversion for specific squawks, customisable via a JSON file
- Custom tag families that use the CCDS-R tag items
- Custom target data block (TDB) alerts, customisable via a JSON file
- **_COMING SOON:_** customisable TDB color alerts, such as STCA, oCAT, CAIT etc.

## Contents
[FAQs](#faq)  
[Installation](#installation)  
[Customisation](#customisation)  
[Troubleshooting](#troubleshooting)


# FAQ

I appreciate that if you're not familiar with these systems, that's a lot of acronyms. I'll do my best to explain features in this readme as I introduce them. First, the easy questions.

## What is CCDS-R?

Code Callsign Distribution System - Replacement (CCDS-R) is a system that correlates the squawk code an aircraft is wearing with a stored flight plan or otherwise pre-agreed callsign, and therefore allows the callsign and flight plan data to be displayed to the controller on the radar. It is currently used by NATS and NAV CANADA.

## Why do I need CCDS-R?

You don't. If you're looking for a more realistic radar representation for your TDBs, particularly for LTC, this is for you. If not, that's okay too.

## What's all this talk of a JSON file?

I've developed CCDS-R for EuroScope to be completely customisable for the user. If you've got some idea of how a specific airfield you control regularly has their code-callsign-conversion set up, then you can emulate that exactly in CCDS-R for EuroScope.

# Installation

Installation is wonderfully simple.

1. [Download the latest release](https://github.com/quassbutreally/EuroScope-CCDS-R/releases/latest)
2. Extract the `CCDS-R` folder to your `EuroScope\UK\Data\Plugins` folder
3. Extract the `tags.txt` file to your `EuroScope\UK\Data\Settings` folder and overwrite the existing file. **_MAKE A BACKUP OF THE EXISTING FILE FIRST._**
4. You're done!

# Customisation

At the moment, only code-callsign conversions and TDB labels can be customised. All the relevant information and examples are contained in `CCDS-R\Settings\conversions.json`.

# Troubleshooting

## I am getting a message in EuroScope from the plugin saying something is wrong

There are a few possible causes.

### `"Invalid JSON found. Custom Code-callsign conversions and labels will be non-functional."`
There is an error in the `conversions.json` file that is preventing it from being parsed. Have another look. If you're unsure, use [this link](https://jsonlint.com/) to check the validity of your JSON.

### `"Invalid data found in the JSON file. Custom Code-callsign conversions and labels will be non-functional."`
One or more of your custom labels or callsigns is either empty or too long. The maximum is 7 characters.

## EuroScope crashes when I load the plugin / EuroScope tells me CCDS-R has encountered an exception
That shouldn't happen. Save the log, and [raise an issue](https://github.com/quassbutreally/EuroScope-CCDS-R/issues/new) with the log file and as much information as you can remember about what happened.

## I'm using the custom tag families, but I just have question marks
The plugin hasn't loaded or hasn't loaded correctly. Unload and reload it.

## Nothing looks different?
If you're using easy mode, you won't notice any difference. You can change this by going to `Other Set -> General Settings -> Correlation Mode`
