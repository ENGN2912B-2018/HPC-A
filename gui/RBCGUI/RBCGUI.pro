#-------------------------------------------------
#
# Project created by QtCreator 2018-11-28T12:18:48
#
#-------------------------------------------------

QT       += core gui \
            opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RBCGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        rbcgui.cpp \
    parameter_setting.cpp \
    VTKReader.cpp



HEADERS += \
        rbcgui.h \
    parameter_setting.h \
    VTKReader.h





FORMS += \
        rbcgui.ui



INCLUDEPATH += $$quote(D:\VTK\VTK-8.1.2\VTK-install\include\vtk-8.1) \
               $$quote(D:\VTK\VTK-8.1.2\VTK-install\include\vtk-8.1\vtkObjectFactory.h) \


LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkalglib-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkChartsCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonColor-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonComputationalGeometry-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonDataModel-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonExecutionModel-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonMath-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonMisc-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonSystem-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkCommonTransforms-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkDICOMParser-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkDomainsChemistry-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkDomainsChemistryOpenGL2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkexoIIc-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkexpat-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersAMR-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersExtraction-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersFlowPaths-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersGeneral-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersGeneric-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersGeometry-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersHybrid-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersHyperTree-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersImaging-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersModeling-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersParallel-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersParallelImaging-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersPoints-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersProgrammable-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersSelection-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersSMP-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersSources-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersStatistics-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersTexture-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersTopology-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkFiltersVerdict-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkfreetype-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkGeovisCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkgl2ps-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkglew-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkGUISupportQt-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkGUISupportQtSQL-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkhdf5-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkhdf5_hl-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingColor-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingFourier-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingGeneral-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingHybrid-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingMath-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingMorphological-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingSources-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingStatistics-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkImagingStencil-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkInfovisCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkInfovisLayout-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkInteractionImage-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkInteractionStyle-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkInteractionWidgets-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOAMR-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOEnSight-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOExodus-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOExport-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOExportOpenGL2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOGeometry-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOImage-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOImport-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOInfovis-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOLegacy-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOLSDyna-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOMINC-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOMovie-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIONetCDF-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOParallel-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOParallelXML-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOPLY-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOSQL-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOTecplotTable-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOVideo-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOXML-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkIOXMLParser-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkjpeg-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkjsoncpp-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtklibharu-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtklibxml2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkLocalExample-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtklz4-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkmetaio-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkNetCDF-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtknetcdfcpp-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkoggtheora-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkParallelCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkpng-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkproj4-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingAnnotation-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingContext2D-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingContextOpenGL2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingFreeType-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingGL2PSOpenGL2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingImage-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingLabel-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingLOD-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingOpenGL2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingQt-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingVolume-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkRenderingVolumeOpenGL2-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtksqlite-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtksys-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkTestingGenericBridge-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkTestingIOSQL-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkTestingRendering-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtktiff-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkverdict-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkViewsContext2D-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkViewsCore-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkViewsInfovis-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkViewsQt-8.1.lib)
LIBS += $$quote(D:\VTK\VTK-8.1.2\VTK-install\lib\vtkzlib-8.1.lib)



RESOURCES += \
    myresources.qrc


