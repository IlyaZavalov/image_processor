cmake_minimum_required(VERSION 3.23)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor main.cpp
        aliases.h
        Colors.h
        TArgParser.cpp
        TArgsValidator.h
        TColor.cpp
        TDefaultArgValidator.h
        TFilterInfo.h
        TFilterManager.cpp
        TImage.cpp
        interfaces/ILoadable.h
        interfaces/ILoadable.h
        headers/TBMPHeader.h
        headers/TDIBHeader.h
        headers/THeader.h
        filters/all_filters.h
        filters/TFilter.cpp
        filters/TBlurFilter.cpp
        filters/TCropFilter.cpp
        filters/TEdgeDetectionFilter.cpp
        filters/TFunctionFilter.h
        filters/TGrayscaleFilter.h
        filters/TMatrixFilter.cpp
        filters/TNegativeFilter.h
        filters/TSharpeningFilter.h
        )
