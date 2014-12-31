// HeatmapGenerator is a graphical user interface software program written in R, C++, and OpenGL to create customized
// gene expression heatmaps from RNA-seq and microarray data in medical research.

// Copyright (C) 2014 Bohdan Khomtchouk and Derek Van Booven

// HeatmapGenerator is peer-reviewed published software financially supported by the United States Department of Defense through
// the National Defense Science and Engineering Graduate Fellowship (NDSEG) Program. Please cite:

// Khomtchouk et al.: HeatmapGenerator: high performance RNAseq and microarray visualization software suite to examine
// differential gene expression levels using an R and C++ hybrid computational pipeline. Source Code for Biology and Medicine
// 2014 9:30

// To compile this source code, do: fltk-config --use-images --use-gl --compile HeatmapGenerator_Macintosh_OSX.cxx

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.





// GUI generated by Fast Light User Interface Designer (fluid) version 1.0302

#include "heatmap.h"
#include <FL/Fl_Native_File_Chooser.H>
#include <iostream>
#include <sys/uio.h>
#include <stdio.h>
#include <sys/types.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/x.H>
#include <dirent.h>
#include <unistd.h>
#include <mach-o/dyld.h>


using namespace std;

Fl_Input *G_filename = NULL;
int heatmap2;
int heatmap;
int ping;
int jpg;
string lowval;
string highval;
string f_name;
Fl_Box* b;
Fl_JPEG_Image* myimage;
Fl_Check_Browser* browser;
string tmp;



void about_callback(Fl_Widget* obj, void*);
void check_callback(Fl_Widget* obj, void*);
void existing_callback(Fl_Widget* obj, void*);
void about_callback(Fl_Widget* obj, void*);
void instructions_callback(Fl_Widget*, void*);
void Butt_CB(Fl_Widget*, void*);
void heatmap2_callback(Fl_Widget*, void*);
void heatmap_callback(Fl_Widget*, void*);
void lowblue(Fl_Widget*, void*);
void lowgreen(Fl_Widget*, void*);
void lowred(Fl_Widget*, void*);
void lowpurple(Fl_Widget*, void*);
void lowred(Fl_Widget*, void*);
void loworange(Fl_Widget*, void*);
void lowyellow(Fl_Widget*, void*);
void highblue(Fl_Widget*, void*);
void highgreen(Fl_Widget*, void*);
void highpurple(Fl_Widget*, void*);
void highred(Fl_Widget*, void*);
void highorange(Fl_Widget*, void*);
void highyellow(Fl_Widget*, void*);
void jpeg1(Fl_Widget*, void*);
void ping1(Fl_Widget*, void*);
int init1();


void heatmap2_callback(Fl_Widget*, void*)
{
	
	if (heatmap2 == 1) {
		heatmap2 = 0;
	}
	else {
		heatmap2 = 1;
		heatmap = 0;
	}
	
	
}

void heatmap_callback(Fl_Widget*, void*)
{
	
	if (heatmap == 1) {
		heatmap = 0;
	}
	else {
		heatmap = 1;
		heatmap2 = 0;
	}
	
}


void Butt_CB(Fl_Widget*, void*) {
	// Create native chooser
	ofstream myfile;
	std::string fname;
	std::string fname2;
	size_t pos = 0;
	std::string oldStr;
	std::string newStr;

	Fl_Native_File_Chooser *chooser = new Fl_Native_File_Chooser();
	chooser->directory("./");
	chooser->title("Open a data file");
	switch (chooser->show()) {
	case -1:    // ERROR
		fprintf(stderr, "*** ERROR show() failed:%s\n", chooser->errmsg());
		break;
	case 1:     // CANCEL
		fprintf(stderr, "*** CANCEL\n");
		return;
		break;
	default:    // USER PICKED A FILE
		fprintf(stderr, "Filename was '%s'\n", chooser->filename());
		fname = chooser->filename();
		break;
	}
	// Move onto the heatmapgeneration now!

	fname2 = fname + ".jpg";
	oldStr = "\\";
	newStr = "\\\\";
	while ((pos = fname.find(oldStr, pos)) != std::string::npos)
	{
		fname.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}



	if (heatmap2 == 1) {
		myfile.open("temp.R");
		myfile << "HeatmapGenerator <- function() {\n";
		myfile << "infile <- \"" + fname + "\"\n";
		myfile << "genexp <- read.table(infile, header = TRUE, sep=\"\t\", stringsAsFactors=FALSE)\n";
		myfile << "names_genexp <-genexp[, 1]\n";
		myfile << "genexp <- data.matrix(genexp[-1])\n";
		myfile << "install.packages(\"gplots_2.14.2.tar.gz\", repos=NULL, type=\"source\")\n";
		myfile << "require (gplots)\n";
		myfile << "row.names(genexp) <- names_genexp\n";
		if (ping == 1) {
			myfile << "outfile <- \"" + fname + ".png\"\n";

			myfile << "png(outfile , width=20, height=20, units=\"cm\", res=600)\n";
		}
		else if (jpg == 1) {
			myfile << "outfile <- \"" + fname + ".jpg\"\n";

			myfile << "jpeg(outfile , width=20, height=20, units=\"cm\", res=600)\n";
		}
		else {
			myfile << "outfile <- \"" + fname + ".tif\"\n";

			myfile << "tiff(outfile , width=20, height=20, units=\"cm\", res=600)\n";

		}
		myfile << "heatmap.2(genexp, Rowv=NA, Colv=NA, col = colorpanel (256, low=\"" + lowval + "\", high=\"" + highval + "\"), scale=\"row\", margins=c(5,10), cexRow=0.5, cexCol=0.7)\n";
		myfile << "outfile <- \"" + fname + ".jpg\"\n";
		myfile << "jpeg(outfile , width=20, height=20, units=\"cm\", res=600)\n";
		myfile << "heatmap.2(genexp, Rowv=NA, Colv=NA, col = colorpanel (256, low=\"" + lowval + "\", high=\"" + highval + "\"), scale=\"row\", margins=c(5,10), cexRow=0.5, cexCol=0.7)\n";
		myfile << "dev.off(which = dev.cur())\n}\nHeatmapGenerator()\nrm(HeatmapGenerator)\n";
		myfile.close();
		system("Rscript temp.R");
	} 
	else{
		myfile.open("temp.R");
		myfile << "HeatmapGenerator <- function() {\n";
		myfile << "infile <- \"" + fname + "\"\n";
		myfile << "genexp <- read.table(infile, header = TRUE, sep=\"\t\", stringsAsFactors=FALSE)\n";
		myfile << "names_genexp <-genexp[, 1]\n";
		myfile << "genexp <- data.matrix(genexp[-1])\n";
		myfile << "install.packages(\"gplots_2.14.2.tar.gz\", repos=NULL, type=\"source\")\n";
		myfile << "require (gplots)\n";
		myfile << "row.names(genexp) <- names_genexp\n";
		if (ping == 1) {
			myfile << "outfile <- \"" + fname + ".png\"\n";
			myfile << "png(outfile , width=20, height=20, units=\"cm\", res=600)\n";

		}
		else if (jpg == 1) {
			myfile << "outfile <- \"" + fname + ".jpg\"\n";
			myfile << "jpeg(outfile , width=20, height=20, units=\"cm\", res=600)\n";

		}
		else {
			myfile << "outfile <- \"" + fname + ".tif\"\n";
			myfile << "tiff(outfile , width=20, height=20, units=\"cm\", res=600)\n";


		}
		myfile << "heatmap(genexp, Rowv=NA, Colv=NA, col = colorpanel (256, low=\"" + lowval + "\", high=\"" + highval + "\"), scale=\"row\", margins=c(5,10), cexRow=0.5, cexCol=0.7)\n";
		myfile << "outfile <- \"" + fname + ".jpg\"\n";
		myfile << "jpeg(outfile , width=20, height=20, units=\"cm\", res=600)\n";
		myfile << "heatmap(genexp, Rowv=NA, Colv=NA, col = colorpanel (256, low=\"" + lowval + "\", high=\"" + highval + "\"), scale=\"row\", margins=c(5,10), cexRow=0.5, cexCol=0.7)\n";
		myfile << "dev.off(which = dev.cur())\n}\nHeatmapGenerator()\nrm(HeatmapGenerator)\n";
		myfile.close();
		system("Rscript temp.R");
	}

	fl_register_images();

	//MessageBox(NULL, fname2.c_str(), "Msg", MB_OK | MB_ICONERROR);
	Fl_Double_Window* o = new Fl_Double_Window(1000, 1000);
	{ 
		Fl_Box *b = new Fl_Box(10, 10, 1000, 1000);
		Fl_Shared_Image *img;
		img = Fl_Shared_Image::get(fname2.c_str());
		if (img->w() > b->w() || img->h() > b->h()) {
			Fl_Image *temp;
			if (img->w() > img->h()) temp = img->copy(b->w(), b->h() * img->h() / img->w());
			else temp = img->copy(b->w() * img->w() / img->h(), b->h());

			img->release();
			img = (Fl_Shared_Image *)temp;
		}
		b->image(img);
		b->redraw();

	
	} // Fl_Box* o
	o->end();
	o->show();

}


int main(int argc, char **argv, const char *env[], const char *path[]) {
	
	DIR *dir;
	long hFile;
	int i;

	i = init1();
	if (i == 0) {
		return 0;
	}
    
	

	// Put initialization here ...  Check for config file, if no config file check for R, if no R then prompt user for R directory.
	Fl_Double_Window* w;
	{ Fl_Double_Window* o = new Fl_Double_Window(601, 361, "HeatmapGenerator");
	w = o;
	o->labeltype(FL_NORMAL_LABEL);
	
    { Fl_Button* o = new Fl_Button(25, 31, 210, 25, "Instructions");
        o->callback((Fl_Callback*)instructions_callback);
    } // Fl_Button* o
 
	{
		Fl_Button *but = new Fl_Button(25, 101, 210, 25, "Create New Heatmap");

		but->callback(Butt_CB);
		//Fl_Box *dummy = new Fl_Box(80, 0, 430, 100);
		//dummy->hide();
		//win->resizable(dummy);

	} // Fl_Button* o
	{ 
		Fl_Button *existing = new Fl_Button(25, 303, 210, 25, "Choose from Existing Heatmaps");
		existing->callback(existing_callback);

	} // Fl_Button* o
	
		{ Fl_Group* o = new Fl_Group(300, 55, 105, 150, "Low Value");
		{ Fl_Round_Button* o = new Fl_Round_Button(308, 75, 25, 25, "Blue");
		o->type(102);
		o->down_box(FL_ROUND_DOWN_BOX);
		o->callback(lowblue);
		} // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(308, 56, 25, 25, "Green");
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->type(102);
	  o->setonly();
	  lowval = "green";
	  o->callback(lowgreen);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(308, 95, 25, 25, "Purple");
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->type(102);
	  o->callback(lowpurple);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(308, 118, 25, 25, "Red");
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->type(102);
	  o->callback(lowred);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(308, 141, 25, 25, "Orange");
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->type(102);
	  o->callback(loworange);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(309, 162, 25, 25, "Yellow");
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->type(102);
	  o->callback(lowyellow);
	  } // Fl_Round_Button* o
		o->end();
		} // Fl_Group* o
		{ Fl_Group* o = new Fl_Group(400, 55, 130, 150, "High Value");
		{ Fl_Round_Button* o = new Fl_Round_Button(408, 75, 25, 25, "Blue");
		o->type(102);
		o->down_box(FL_ROUND_DOWN_BOX);
		o->callback(highblue);
		} // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(408, 56, 25, 25, "Green");
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->type(102);
	  o->callback(highgreen);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(408, 95, 25, 25, "Purple");
	  o->type(102);
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->callback(highpurple);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(408, 118, 25, 25, "Red");
	  o->type(102);
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->setonly();
	  highval = "red";
	  o->callback(highred);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(408, 141, 25, 25, "Orange");
	  o->type(102);
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->callback(highorange);
	  } // Fl_Round_Button* o
	  { Fl_Round_Button* o = new Fl_Round_Button(409, 162, 25, 25, "Yellow");
	  o->type(102);
	  o->down_box(FL_ROUND_DOWN_BOX);
	  o->callback(highyellow);
	  } // Fl_Round_Button* o
		o->end();
		} // Fl_Group* o
	{ new Fl_Box(385, 10, 25, 25, "Change Color");
	} // Fl_Box* o


	{ new Fl_File_Input(25, 54, 210, 43);
	} // Fl_File_Input* o
	{ //Fl_Browser o(25, 137, 210, 163);
	std::ofstream outfile;
	outfile.open("existing.dat");
	browser = new Fl_Check_Browser(25,137,210,163);
        
        
        DIR *dp;
        char *subit;
        struct dirent *ep;
        
        std::string s(path[0]);
        
        std::cout << "size is " << s.size() << std::endl;
        std::string filepath1 = s.substr(0,s.size()-16);
        std::cout << "size is " << filepath1 << std::endl;
        dp = opendir (filepath1.c_str());
        std::cout << "path is : " << s << std::endl;
        
        string s_cwd=getcwd(NULL,0);
        fprintf(stderr,"working directory is %s\n",s_cwd.c_str());
        
        if (dp != NULL)
        {
            fprintf(stderr, "within main dp loop\n");
            while (ep = readdir(dp)) {
                
                    subit = strstr(ep->d_name,".jpg");
                    puts(ep->d_name);
                    if (subit != NULL) {
                        browser->add(ep->d_name);
                    }
                
            }
        }
        fprintf(stderr,"past loading\n");
        
	browser->callback((Fl_Callback*)check_callback);
	browser->when(FL_WHEN_RELEASE);
	
	} // Fl_File_Browser* o
	{ Fl_Button* o = new Fl_Button(311, 302, 118, 23, "About");
	o->callback((Fl_Callback*)about_callback);
	} // Fl_Button* o
	{ new Fl_Box(25, 3, 215, 25, "Welcome to HeatmapGenerator!");
	} // Fl_Box* o
	{ Fl_Check_Button* o = new Fl_Check_Button(459, 249, 105, 25, "PNG");
	o->down_box(FL_DOWN_BOX);
	ping = 0;
	o->callback(ping1);
	} // Fl_Check_Button* o
	{ new Fl_Box(459, 219, 125, 25, "Save Image As");
	} // Fl_Button* o
	{ Fl_Check_Button* o = new Fl_Check_Button(531, 249, 105, 25, "JPG");
	o->down_box(FL_DOWN_BOX);
	jpg = 0;
	o->callback(jpeg1);
	} // Fl_Check_Button* o
	{ Fl_Group* o = new Fl_Group(305, 240, 140, 60, "Heatmap Type");
	{ Fl_Check_Button* o = new Fl_Check_Button(315, 245, 20, 25, "Simple Heatmap");
	o->down_box(FL_DOWN_BOX);
	heatmap = 0;
	o->type(102);
	o->callback(heatmap_callback);
	} // Fl_Check_Button* o
	  { Fl_Check_Button* o = new Fl_Check_Button(315, 265, 20, 25, "Advanced Heatmap");
	  o->down_box(FL_DOWN_BOX);
	  o->value(1);
	  heatmap2 = 1;
	  o->callback(heatmap2_callback);
	  o->type(102);
	  o->setonly();
	  } // Fl_Check_Button* o
	o->end();
	} // Fl_Group* o
	o->end();
	} // Fl_Double_Window* o
  {
  } // Fl_Double_Window* o
	w->show(argc, argv);
	return Fl::run();
}

void about_callback(Fl_Widget* obj, void*)
{
	Fl_Double_Window* o = new Fl_Double_Window(476, 362);
	{ new Fl_Box(150, 115, 160, 95, "Copyright 2014 Bohdan Khomtchouk and Derek Van Booven\n\n    This program is \
free software: you can redistribute it and/or modify\n    it under the terms o\
f the GNU General Public License as published by\n    the Free Software Founda\
tion, either version 3 of the License, or\n    (at your option) any later vers\
ion.\n\n    This program is distributed in the hope that it will be useful,\n \
but WITHOUT ANY WARRANTY; without even the implied warranty of\n    MERCHAN\
TABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See\n    the GNU General Public License \
for more details.\n\n    You should have received a copy of the GNU G\
eneral Public License\n    along with this program.  If not, see <http://www.g\
nu.org/licenses/>.");
	} // Fl_Box* o
	o->end();
	o->show();

}
                 
void instructions_callback(Fl_Widget*, void*)
{
       Fl_Double_Window* o = new Fl_Double_Window(476, 262);
       { new Fl_Box(150, 115, 160, 20, "Please read HeatmapGenerator Manual downloaded with\nthis program before use.\n\n  \
              \n Please make sure that the file you choose is:\n\n    #1) Similar in \
style to EXAMPLE.txt (downloaded with this program) \n  #2) Feel free to try EXAMPLE.txt the first time you use this program\n\n");
       } // Fl_Box* o
       o->end();
       o->show();
 
}


void lowblue(Fl_Widget*, void*)
{
	lowval = "blue";
}
void lowgreen(Fl_Widget*, void*)
{
	lowval = "green";
}
void lowpurple(Fl_Widget*, void*)
{
	lowval = "purple";
}
void lowred(Fl_Widget*, void*)
{
	lowval = "red";
}
void loworange(Fl_Widget*, void*)
{
	lowval = "orange";
}
void lowyellow(Fl_Widget*, void*)
{
	lowval = "yellow";
}
void highblue(Fl_Widget*, void*)
{
	highval = "blue";
}
void highgreen(Fl_Widget*, void*)
{
	highval = "green";
}
void highpurple(Fl_Widget*, void*)
{
	highval = "purple";
}
void highred(Fl_Widget*, void*)
{
	highval = "red";
}
void highorange(Fl_Widget*, void*)
{
	highval = "orange";
}
void highyellow(Fl_Widget*, void*)
{
	highval = "yellow";
}
void jpeg1(Fl_Widget*, void*)
{
	if (jpg == 1) {
		jpg = 0;
	}
	else {
		jpg = 1;
	}
}
void ping1(Fl_Widget*, void*)
{
	if (ping == 1) {
		ping = 0;
	}
	else {
		ping = 1;
	}
}

void existing_callback(Fl_Widget*, void*)
{
	
	fl_register_images();
	Fl_Double_Window* o = new Fl_Double_Window(1000, 1000);
	{
		Fl_Box *b = new Fl_Box(10, 10, 1000, 1000);
		Fl_Shared_Image *img;
		
        char path[1024];
		uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) == 0)
            fprintf(stderr,"path is %s", path);
		std::string f = std::string(path);
		std::string dname = f.substr(0, f.find_last_of("\\/"));
		
		f_name = dname + "/" + f_name;
		fprintf(stderr, "*** debug ERROR : %s\n", f_name.c_str());
		img = Fl_Shared_Image::get(f_name.c_str());
		
		if (img->w() > b->w() || img->h() > b->h()) {
			Fl_Image *temp;
			if (img->w() > img->h()) temp = img->copy(b->w(), b->h() * img->h() / img->w());
			else temp = img->copy(b->w() * img->w() / img->h(), b->h());
			
			img->release();
			img = (Fl_Shared_Image *)temp;
		}
		
		b->image(img);
		b->redraw();


	} // Fl_Box* o
	o->end();
	o->show();
	//browser->clear();

}

void check_callback(Fl_Widget*, void*)
{
	
	f_name = browser->text(browser->value());
	
}

int init1()
{

	string path;
	ifstream myfile;
	string line;
	system("which RScript > config");
	myfile.open("config");
	getline(myfile, line);
	int i = line.find("INFO");

	fprintf(stderr, "%d\n", i);

	if (i == 0) {
		//MessageBox(NULL, "Cannot find Rscript in path, please read instructions on how to properly setup R", "Msg", MB_OK | MB_ICONERROR);
		return 0;
	}
	else {
		return 1;
	}
}

