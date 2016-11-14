include_directories(catch)
include_directories(vibes)

ADD_EXECUTABLE(test_Polar test_polar.cpp)
target_link_libraries(test_Polar ${LIBS} ibex-geometry)
ADD_TEST(test_Polar test_Polar)

ADD_EXECUTABLE(test_CtcSegment TestCtcSegment.cpp)
target_link_libraries(test_CtcSegment ${LIBS} ibex-geometry )
ADD_TEST(test_CtcSegment test_CtcSegment)

ADD_EXECUTABLE(test_SepPolygon TestSepPolygon.cpp vibes/vibes.cpp)
target_link_libraries(test_SepPolygon ${LIBS} ibex-geometry )
ADD_TEST(test_SepPolygon test_SepPolygon)
