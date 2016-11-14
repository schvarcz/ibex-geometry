//============================================================================
//                                  I B E X
// File        : TestSepPolygon.cpp
// Author      : Benoit Desrochers
// Copyright   : Ecole des Mines de Nantes (France)
// License     : See the LICENSE file
// Created     : Jan 02, 2015
//============================================================================


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "catch_interval.hpp"
#include "vibes/vibes.h"

#include "ibex_SepPolygon.h"

using namespace ibex;
using namespace Catch;
using namespace Detail;

std::vector<double> murs_xa, murs_xb, murs_ya, murs_yb, murs_xa2, murs_xb2, murs_ya2, murs_yb2;

void setup(){

    murs_xa.clear(); murs_xa2.clear();
    murs_xb.clear(); murs_xb2.clear();
    murs_ya.clear(); murs_ya2.clear();
    murs_yb.clear(); murs_yb2.clear();

    // Polygone convex
    murs_xa.push_back(6);  murs_ya.push_back(-6);   murs_xb.push_back(7);  murs_yb.push_back(9);
    murs_xa.push_back(7);  murs_ya.push_back(9);   murs_xb.push_back(0);  murs_yb.push_back(5);
    murs_xa.push_back(0);  murs_ya.push_back(5);    murs_xb.push_back(-9); murs_yb.push_back(8);
    murs_xa.push_back(-9); murs_ya.push_back(8);    murs_xb.push_back(-8); murs_yb.push_back(-9);
    murs_xa.push_back(-8); murs_ya.push_back(-9);   murs_xb.push_back(6);  murs_yb.push_back(-6);

    // Objet au milieu
    murs_xa2.push_back(-2); murs_ya2.push_back(3);   murs_xb2.push_back(3.5);  murs_yb2.push_back(2);
    murs_xa2.push_back(3.5); murs_ya2.push_back(2);   murs_xb2.push_back(3);  murs_yb2.push_back(-4);
    murs_xa2.push_back(3); murs_ya2.push_back(-4);   murs_xb2.push_back(-3);  murs_yb2.push_back(-3);
    murs_xa2.push_back(-3); murs_ya2.push_back(-3);   murs_xb2.push_back(-2);  murs_yb2.push_back(3);
}

TEST_CASE("test_SepPolygon_01", "")
{
    setup();

    SepPolygon S1(murs_xa, murs_ya, murs_xb, murs_yb);

    IntervalVector box(2);
    box[0]=Interval(-10,10);
    box[1]=Interval(-10,10);

}

TEST_CASE("test_SepPolygon_02", "")
{
    setup();
    murs_xa.insert(murs_xa.end(), murs_xa2.begin(), murs_xa2.end());
    murs_ya.insert(murs_ya.end(), murs_ya2.begin(), murs_ya2.end());
    murs_xb.insert(murs_xb.end(), murs_xb2.begin(), murs_xb2.end());
    murs_yb.insert(murs_yb.end(), murs_yb2.begin(), murs_yb2.end());

    SepPolygon S1(murs_xa, murs_ya, murs_xb, murs_yb);
}

TEST_CASE("test_SepPolygon_03", "")
{
    setup();
    SepPolygon S1(murs_xa, murs_ya, murs_xb, murs_yb);
    SepPolygon S2(murs_xa2, murs_ya2, murs_xb2, murs_yb2);
    SepNot S3(S2);
    SepInter S(S1, S3);
}

TEST_CASE("test_SepPolygon_04", "")
{

    double ls[6][4] = {
        {2.5, 0., 3, 0.},
        {3., 0., 7., 6.},
        {7., 6., 1., 12.},
        {1., 12., -7., 8.},
        {-7., 8., -3., -3.},
        {-3., -3., 2.5, 0.}
    };

    std::vector< std::vector< std::vector<double> > > lines(sizeof(ls)/sizeof(ls[0]));
    for(int i =0; i < sizeof(ls)/sizeof(ls[0]); i++)
    {
        lines[i].resize(2);
        lines[i][0].insert(lines[i][0].begin(), ls[i]  , ls[i]+2);
        lines[i][1].insert(lines[i][1].begin(), ls[i]+2, ls[i]+4);
    }

    std::vector<double>ax, ay, bx, by;
    ax.resize(lines.size()); ay.resize(lines.size()); bx.resize(lines.size()); by.resize(lines.size());
    for(int i=0; i< lines.size(); i++)
    {
        ax[i] = lines[i][0][0];
        ay[i] = lines[i][0][1];
        bx[i] = lines[i][1][0];
        by[i] = lines[i][1][1];
    }

    SepPolygon sep(ax,ay,bx,by);

    IntervalVector box_in(2,Interval(-15,15));
    IntervalVector box_out(2,Interval(-15,15));

    sep.separate(box_in, box_out);
    std::cout << box_in << std::endl;
    std::cout << box_out << std::endl;



    double _resbox[][2] = {{-7,7},  {-3,12}};
    IntervalVector resbox(2,_resbox);

    CHECK(box_in == resbox);
    CHECK(box_out == resbox);

    vibes::beginDrawing();
    vibes::newFigure("test_SepPolygon_04");

    vibes::drawBox(box_in,"k[r]");
    vibes::drawBox(box_out,"k[c]");

    for(int i =0; i< lines.size(); i++)
        vibes::drawLine(lines[i],"k");
}



TEST_CASE("test_SepPolygon_05", "")
{

    double ls[8][4] = {
        {2.5, 0., 2.5, 5.},
        {2.5, 5., 3., 5.},
        {3., 5., 3., 0.},
        {3., 0., 7., 6.},
        {7., 6., 1., 12.},
        {1., 12., -7., 8.},
        {-7., 8., -3., -3.},
        {-3., -3., 2.5, 0.}
    };

    std::vector< std::vector< std::vector<double> > > lines(sizeof(ls)/sizeof(ls[0]));
    for(int i =0; i < sizeof(ls)/sizeof(ls[0]); i++)
    {
        lines[i].resize(2);
        lines[i][0].insert(lines[i][0].begin(), ls[i]  , ls[i]+2);
        lines[i][1].insert(lines[i][1].begin(), ls[i]+2, ls[i]+4);
    }

    std::vector<double>ax, ay, bx, by;
    ax.resize(lines.size()); ay.resize(lines.size()); bx.resize(lines.size()); by.resize(lines.size());
    for(int i=0; i< lines.size(); i++)
    {
        ax[i] = lines[i][0][0];
        ay[i] = lines[i][0][1];
        bx[i] = lines[i][1][0];
        by[i] = lines[i][1][1];
    }

    SepPolygon sep(ax,ay,bx,by);

    IntervalVector box_in(2,Interval(-15,15));
    IntervalVector box_out(2,Interval(-15,15));

    sep.separate(box_in, box_out);
    std::cout << box_in << std::endl;
    std::cout << box_out << std::endl;



    double _resbox[][2] = {{-7,7},  {-3,12}};
    IntervalVector resbox(2,_resbox);

    CHECK(box_in == resbox);
    CHECK(box_out == resbox);

    vibes::beginDrawing();
    vibes::newFigure("Polygon");

    vibes::drawBox(box_in,"k[r]");
    vibes::drawBox(box_out,"k[c]");

    for(int i =0; i< lines.size(); i++)
        vibes::drawLine(lines[i],"k");
}

