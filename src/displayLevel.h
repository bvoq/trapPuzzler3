
//
//  displayLevel.h
//  trapStory
//
//  Created by Kivifreak on 25/12/15.
//
//

#ifndef trapPuzzler3_displayLevel_h
#define trapPuzzler3_displayLevel_h

int LINE_WIDTH = 5;


void gradientFilledRect(float x, float y, float w, float h, ofColor tl, ofColor tr, ofColor bl, ofColor br) {
    ofMesh temp;
    temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    temp.addVertex( ofPoint(x,y) );
    temp.addColor(tl);
    temp.addVertex( ofPoint(x+w,y) );
    temp.addColor(tr);
    temp.addVertex( ofPoint(x+w,y+h) );
    temp.addColor(bl);
    temp.addVertex( ofPoint(x,y+h) );
    temp.addColor(br);
    temp.draw();
}


void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY) {
    float cp1x = prevX + 2.0/3.0*(cpx - prevX);
    float cp1y = prevY + 2.0/3.0*(cpy - prevY);
    float cp2x = cp1x + (x - prevX)/3.0;
    float cp2y = cp1y + (y - prevY)/3.0;
    
    // finally call cubic Bezier curve function
    ofBezierVertex(cp1x, cp1y, cp2x, cp2y, x, y);
};



void roundedRect(float x, float y, float w, float h, float r) {
    ofBeginShape();
    ofVertex(x+r, y);
    ofVertex(x+w-r, y);
    quadraticBezierVertex(x+w, y, x+w, y+r, x+w-r, y);
    ofVertex(x+w, y+h-r);
    quadraticBezierVertex(x+w, y+h, x+w-r, y+h, x+w, y+h-r);
    ofVertex(x+r, y+h);
    quadraticBezierVertex(x, y+h, x, y+h-r, x+r, y+h);
    ofVertex(x, y+r);
    quadraticBezierVertex(x, y, x+r, y, x, y+r);
    ofEndShape();
}

/*
 void gradientFilledRoundedRect(float x, float y, float w, float h, float r, ofFloatColor top, ofFloatColor bot) {
 ofPolyline poly;
 poly.addVertex(x,y+r); //top left - under corner
 //while(colors.size() < poly.size()) colors.push_back(top);
 poly.arc(ofPoint(x+r, y+r),r,r,180,270,true,CIRCLE_RESOLUTION);
 //while(colors.size() < poly.size()) colors.push_back(top);
 
 poly.addVertex(x+w-r,y); //top right - left from corner
 //while(colors.size() < poly.size()) colors.push_back(top);
 poly.arc(ofPoint(x+w-r, y+r),r,r,280,360,true,CIRCLE_RESOLUTION);
 //while(colors.size() < poly.size()) colors.push_back(top);
 
 poly.addVertex(x+w, y+h-r); //bottom right - above corner
 //while(colors.size() < poly.size()) colors.push_back(bot);
 poly.arc(ofPoint(x+w-r, y+h-r),r,r,0,90,true,CIRCLE_RESOLUTION);
 //while(colors.size() < poly.size()) colors.push_back(bot);
 
 poly.addVertex(x+r,y+h); //bottom left - right from corner
 //while(colors.size() < poly.size()) colors.push_back(bot);
 poly.arc(ofPoint(x+r, y+h-r),r,r,90,180,true,CIRCLE_RESOLUTION);
 //while(colors.size() < poly.size()) colors.push_back(bot);
 poly.addVertex(x,y+r);
 
 ofSetColor(ofColor::blue);
 //poly.draw();
 
 ofMesh m;
 ofTessellator tess;
 tess.tessellateToMesh(poly, OF_POLY_WINDING_ODD, m, true);
 
 
 vector<ofVec3f> meshVertices = m.getVertices();
 vector<ofFloatColor> colors(meshVertices.size());
 for(int i = 0; i < meshVertices.size(); ++i) {
 if(meshVertices[i].y < y+h/2) colors[i] = top;
 else colors[i] = bot;
 }
 
 m.addColors(colors);
 cout << "Sizerino:" << m.getNumVertices() << " " << colors.size() << " " << poly.size() << endl;
 //ofNoFill();
 m.draw();
 
 //void ofPolyline::arc(float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd, int circleResolution=20)
 
 //ofMesh temp;
 //temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
 ////temp.addVertex( ofPoint(x,y) );
 //temp.addVertex( ofPoint(x+r,y) );    //top left - right from corner
 //temp.addVertex( ofPoint(x+w-r,y) );  //top right - left from corner
 //temp.addColor(scheme.colorBACKGROUND);
 //temp.addVertex( ofPoint(x+w,y) );
 //temp.addColor(scheme.colorBACKGROUND);
 //temp.addVertex( ofPoint(x,y+h) );
 //temp.addColor(scheme.colorBACKGROUND_SHADED);
 //temp.addVertex( ofPoint(x+w,y+h) );
 //temp.addColor(scheme.colorBACKGROUND_SHADED);
 //temp.draw();
 
 }*/

int CIRCLE_RESOLUTION = 50;


//2^4 possibilities of mesh = 16 pre-processing

ofMesh generateMeshTile(float w, float h, float r, ofFloatColor tlc, ofFloatColor trc, ofFloatColor blc, ofFloatColor brc, bool neighL=false, bool neighR=false, bool neighU=false, bool neighD=false) {
    ofPolyline poly;
    
    //top left - under corner
    if(neighL || neighU) poly.addVertex(0,0);
    else {
        poly.addVertex(0,0+r);
        poly.arc(ofPoint(0+r, 0+r),r,r,180,270,true,CIRCLE_RESOLUTION);
    }
    
    //top right - left from corner
    if (neighU || neighR) poly.addVertex(w,0);
    else {
        poly.addVertex(0+w-r,0);
        poly.arc(ofPoint(0+w-r, 0+r),r,r,280,360,true,CIRCLE_RESOLUTION);
    }
    
    //bottom right - above corner
    if(neighR || neighD) poly.addVertex(w,h);
    else {
        poly.addVertex(0+w, 0+h-r);
        poly.arc(ofPoint(0+w-r, 0+h-r),r,r,0,90,true,CIRCLE_RESOLUTION);
    }
    
    
    //bottom left - right from corner
    if(neighD || neighL) poly.addVertex(0,h);
    else {
        poly.addVertex(0+r,0+h);
        poly.arc(ofPoint(0+r, 0+h-r),r,r,90,180,true,CIRCLE_RESOLUTION);
    }
    
    //Add first/last point again
    //if(neighL || neighU) poly.addVertex(0,0);
    //else poly.addVertex(0,0+r);
    
    ofMesh m;
    ofTessellator tess;
    tess.tessellateToMesh(poly, OF_POLY_WINDING_ODD, m, true);
    
    
    vector<ofVec3f> meshVertices = m.getVertices();
    vector<ofFloatColor> colors(meshVertices.size());
    for(int i = 0; i < meshVertices.size(); ++i) {
        if(meshVertices[i].y < h/2 && meshVertices[i].x < w/2) colors[i] = tlc;
        else if(meshVertices[i].y < h/2 && meshVertices[i].x >= w/2) colors[i] = trc;
        else if(meshVertices[i].y >= h/2 && meshVertices[i].x < w/2) colors[i] = blc;
        else if(meshVertices[i].y >= h/2 && meshVertices[i].x >= w/2) colors[i] = brc;
        else DEB("Weird error at ofMeshGenerateTile with i " << i << " and " << meshVertices[i].x << " " << meshVertices[i].y);
    }
    m.addColors(colors);
    return m;
}



vector<ofMesh> fancyMeshes; //store all
void generateFancyMeshes() {
    float w = 1*50, h = 1*50;
    float r = .05*50;
    
    for(int i = 0; i < 32; ++i) {
        ofMesh m;
        ofPolyline poly;
        ofTessellator tess;
        
        //top left
        if((1<<1)&i || (1<<3)&i) poly.addVertex(0,0);
        else {
            poly.addVertex(0,0+r);
            poly.arc(ofPoint(0+r, 0+r),r,r,180,270,true,CIRCLE_RESOLUTION);
        }
        
        //top right
        if ((1<<1)&i || (1<<2)&i) poly.addVertex(w,0);
        else {
            poly.addVertex(0+w-r,0);
            poly.arc(ofPoint(0+w-r, 0+r),r,r,280,360,true,CIRCLE_RESOLUTION);
        }
        
        //bottom right
        if((1<<0)&i || (1<<2)&i) poly.addVertex(w,h);
        else {
            poly.addVertex(0+w, 0+h-r);
            poly.arc(ofPoint(0+w-r, 0+h-r),r,r,0,90,true,CIRCLE_RESOLUTION);
        }
        
        
        //bottom left
        if((1<<0)&i || (1<<3)&i) poly.addVertex(0,h);
        else {
            poly.addVertex(0+r,0+h);
            poly.arc(ofPoint(0+r, 0+h-r),r,r,90,180,true,CIRCLE_RESOLUTION);
        }
        
        tess.tessellateToMesh(poly, OF_POLY_WINDING_ODD, m, true);
        vector<ofVec3f> meshVertices = m.getVertices();
        vector<ofFloatColor> colors( meshVertices.size(), {scheme.colorLEVELSELECT});
        m.addColors(colors);
        fancyMeshes.push_back(m);
    }
}

void fancyDrawCellFill(int i, int j, float scale, float tScale, deque<deque<int> > & grid) {
    int type = 0; //figure out bitmap 0000lrud
    if(i == 0 || grid[i-1][j] == grid[i][j]) type |= 1 << 3; //left
    if(i == (int)grid.size() - 1 || grid[i+1][j] == grid[i][j]) type |= 1 << 2; //right
    if(j == 0 || grid[i][j-1] == grid[i][j]) type |= 1 << 1; //top
    if(j == (int)grid[i].size() - 1 || grid[i][j+1] == grid[i][j]) type |= 1 << 0; // bottom
    //cout << type << endl;
    fancyMeshes[type].draw();
}


bool isCenterTile(int idX, int idY, deque<deque<int> > & grid) {
    if(idY == 0 || grid[idY-1][idX] != grid[idX][idY]) return false;
    else if(idX == 0 || grid[idY][idX-1] != grid[idX][idY]) return false;
    else if(idY == grid.size() - 1 || grid[idY+1][idY] != grid[idX][idY]) return false;
    else if(idX == grid[0].size() - 1 || grid[idY][idX+1] != grid[idX][idY]) return false;
    else return true;
}

bool tryArcing = true;
void drawCellFill(int i, int j,  float scale, float tScale, deque<deque<int> > & grid) {
    ofFill();
    ofBeginShape();
    
    //Top-Right
    ofVertex(tScale, 0);
    if ((i == 0 || grid[i-1][j] != grid[i][j]) &&
        (j == grid[0].size() - 1 || grid[i][j+1] != grid[i][j])) {
        if(tryArcing) {
            ofCurveVertex(tScale, 0);
            ofCurveVertex(scale - tScale, 0);
            //ofCurveVertex(scale, 0);
            ofCurveVertex(scale, tScale);
            ofCurveVertex(scale, scale - tScale);
        } else {
            ofVertex(scale - tScale, 0);
        }
    }
    else {
        ofVertex(scale, 0);
    }
    
    //Bottom-Right
    ofVertex(scale, tScale);
    if ((i == grid.size() - 1 || grid[i+1][j] != grid[i][j]) &&
        (j == grid[0].size() - 1 || grid[i][j+1] != grid[i][j])) {
        if(tryArcing) {
            ofCurveVertex(scale, tScale);
            ofCurveVertex(scale, scale - tScale);
            ofCurveVertex(scale - tScale, scale);
            ofCurveVertex(tScale, scale);
        } else {
            ofVertex(scale, scale - tScale);
        }
    }
    else {
        ofVertex(scale, scale);
    }
    
    //Bottom-Left
    ofVertex(scale - tScale, scale);
    if ((i == grid.size() - 1 || grid[i+1][j] != grid[i][j]) &&
        (j == 0 || grid[i][j-1] != grid[i][j])) {
        if(tryArcing) {
            ofCurveVertex(scale - tScale, scale);
            ofCurveVertex(tScale, scale);
            ofCurveVertex(0, scale - tScale);
            ofCurveVertex(0, tScale);
        } else {
            ofVertex(tScale, scale);
        }
    }
    else {
        ofVertex(0, scale);
    }
    
    //Top-Left
    ofVertex(0, scale - tScale);
    if ((i == 0 || grid[i-1][j] != grid[i][j]) &&
        (j == 0 || grid[i][j-1] != grid[i][j])) {
        if(tryArcing) {
            ofCurveVertex(0, scale - tScale);
            ofCurveVertex(0, tScale);
            ofCurveVertex(tScale, 0);
            ofCurveVertex(scale - tScale, 0);
        } else {
            ofVertex(0, tScale);
        }
    }
    else {
        ofVertex(0, 0);
    }
    
    ofVertex(tScale, 0);
    
    ofEndShape();
    //fancyDrawCellFill(i,j,scale,tScale,grid); seem to be slower than anticipated
}



void drawCellMonsterFill(int i, int j,  float scale, float tScale, deque<deque<int> > & grid, keyType directionNotExtending) {
    //Color should be set before calling this method.
    ofFill();
    if(directionNotExtending == LEFT) {
        int yP = 0, xP = 0;
        if(i == 0) {
            ofBeginShape();
            ofVertex(xP,yP+scale);
            ofVertex(xP+getWidth(),yP+scale);
            ofVertex(xP+getWidth(),yP-getHeight());
            ofVertex(xP,yP-getHeight());
            ofVertex(xP,yP+scale);
            ofEndShape();
        }
        else if(i+1 == grid.size()) {
            ofBeginShape();
            ofVertex(xP,yP);
            ofVertex(xP+getWidth(),yP);
            ofVertex(xP+getWidth(),yP+getHeight());
            ofVertex(xP,yP+getHeight());
            ofVertex(xP,yP);
            ofEndShape();
        }
        else {
            ofBeginShape();
            ofVertex(xP,yP);
            ofVertex(xP+getWidth(),yP);
            ofVertex(xP+getWidth(),yP+scale);
            ofVertex(xP,yP+scale);
            ofVertex(xP,yP);
            ofEndShape();
        }
        /*
        ofFill();
        ofBeginShape();
        ofVertex(0,0);
        ofVertex(0,-getHeight()*2);
        ofVertex(getWidth()*2,-getHeight()*2);
        ofVertex(getWidth()*2,getHeight()*2);
        ofVertex(0,getHeight()*2);
        ofVertex(0,0);
        ofEndShape();*/
    } else assert(false); //TODO Implement!
    /* FOR FUTURE 1-D BLOCKS
     if((i == 0 || grid[i-1][j] != grid[i][j]) && directionNotExtending != UP) {
     ofFill();
     ofBeginShape();
     ofVertex(0, tScale);
     ofVertex(0,-getHeight()*2);
     ofVertex(0,-getHeight()*2);
     ofVertex(scale,tScale);
     ofVertex(0,tScale);
     ofEndShape();
     }*/
}



void drawMonsterEye(int i, int j, float scale, float tScale, deque<deque<int> > & grid) {
    ofEnableSmoothing();
    ofFill();
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(0,-scale*.1);
    drawCellFill(i,j,scale*1.2,tScale*1.2,grid);
    ofPopMatrix();
    /*
     float angle = atan2( (float)(currentWatchY - i) , (float)(currentWatchX - j) );
     
     //void ofPath::arc(float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd);
     
     ofSetColor(scheme.colorGRAVITYMONSTERSTROKE);
     ofDrawEllipse(scale/2.,scale/2.,scale*.9, scale*.9);
     ofSetColor(255,255,255);
     ofDrawEllipse(scale/2.,scale/2.,scale*.9, scale*.9);
     ofSetColor(scheme.colorENEMY);
     //monsterangleeye = fmod(monsterangleeye,360);
     float offset = 0;
     for(float angle = 0; angle < 2*PI; angle += PI/3.) {
     
     ofPath eyeRed;
     eyeRed.setColor(ofColor(255,0,0));
     eyeRed.setFilled(false);
     eyeRed.setStrokeWidth(1.5);
     eyeRed.moveTo(scale/2.,scale/2.);
     if(offset == PI/4) offset = -PI/2;
     offset += PI/4;
     
     eyeRed.quadBezierTo(
     scale/2., scale/2.,
     scale/2. + scale*.4/2. * sin(angle+offset), scale/2. + scale*.4/2. * cos(angle+offset),
     scale/2. + scale*.9/2. * sin(angle), scale/2. + scale*.9/2. * cos(angle));
     eyeRed.draw();
     }
     ofSetColor(0);
     ofDrawEllipse(scale/2.,scale/2.,scale*.3, scale*.3);*/
    
    for(float a = 0; a <= 1; a += 0.2) {
        float leftPos = (currentWatchY-i) * 1./grid.size() * .25 * scale + scale*.6 * a + scale/2. - scale*.3;
        float rightPos = a*(scale*1.2-2.*tScale*1.2) + tScale*1.2 - scale*.1;
        ofPath eyeRed;
        eyeRed.setColor(ofColor(255,0,0));
        eyeRed.setFilled(false);
        eyeRed.setStrokeWidth(1.5);
        eyeRed.quadBezierTo(0, leftPos, scale/2.,scale/2., scale*1.2, rightPos);
        eyeRed.draw();
    }
    ofPushMatrix();
    ofTranslate(0,(currentWatchY-i) * 1./grid.size() * .25 * scale);
    
    ofPath eyeIris;
    eyeIris.setColor(ofColor(0,0,0));
    eyeIris.setFilled(true);
    eyeIris.moveTo(0,scale/2. - scale*.3);
    eyeIris.arc(0,scale/2.,scale*.2,scale*.3,-90,90);
    eyeIris.draw();
    
    ofPopMatrix();
    //eyeIris.lineTo(0,scale/2. + scale*.3);
    // eyeIris.lineTo(0,scale/2. - scale*.3);
}



int fastrandtoothgenseed = 0;
int fastrandtoothgenint() { //between 0-32767
    fastrandtoothgenseed = (214013*fastrandtoothgenseed+2531011);
    return ((fastrandtoothgenseed>>16)&0x7FFF);
}
float fastrandtoothgennegpos() { //returns between -1. and 1. ^^
    fastrandtoothgenseed = (214013*fastrandtoothgenseed+2531011);
    return (  ((fastrandtoothgenseed>>16)&0x7FFF) - 16383  ) * 1./16384;
}

float fastrandtoothgenpos() { //returns between 0 and 1
    fastrandtoothgenseed = (214013*fastrandtoothgenseed+2531011);
    return (  ((fastrandtoothgenseed>>16)&0x7FFF) ) * 1./32767;
}

void drawMonsterMouth(int i, int j, float scale, float tScale, deque<deque<int> > & grid, ofRectangle &  position) {
    ofSetColor(0);
    if(i==0) {
        ofFill();
        ofDrawRectangle(0,-getHeight(),scale*.8,getHeight()+tScale*.8);
    }
    if(i+1 == grid.size()) {
        ofFill();
        ofDrawRectangle(0,0,scale*.8,getHeight());
    }
    ofSetColor(0);
    drawCellFill(i,j,scale*.8,tScale*.8,grid);
    ofSetColor(0);
    if(i+1 < grid.size() && grid[i+1][j] == grid[i][j]) ofDrawRectangle(0,scale*.8,scale*.8,scale*.1);
    if(i-1 >= 0 && grid[i-1][j] == grid[i][j]) ofDrawRectangle(0,0,scale*.8,-scale*.1);
    
    //if(i+1 < grid.size() && grid[i+1][j] == grid[i][j]) ofDrawRectangle(0,scale*.8,scale*.8,scale);
}


//float prevscale = 0; int prevgridsize = 0;
//unordered_map<int, vector<ofPath> > leftteethDP;
void drawMonsterTeethLeft(int i, int j, float scale, float tScale, deque<deque<int> > & grid, ofRectangle & position) {
    for(int k = 0; j-2 >= 0 && k < grid.size(); ++k) if(getCellType(grid[k][j-2]) == GRAVITYMONSTEREYE || getCellType(grid[k][j-2]) == GRAVITYMONSTERDEADEYE) {
        fastrandtoothgenseed = (1000*(k-i)) % 32767;
        //fastrandtoothgenseed = rand(); for debugging purposes
        break;
    }
    ofSetColor(255);
    
    float teethOffset = scale*.1*fastrandtoothgenpos()+scale*.01;//minsize
    float teethY = -scale*.1;
    if(i-1 >= 0 && i < grid.size() && grid[i-1][j] != grid[i][j]) teethY = scale *.15;
    
    float until = scale*.8;
    if(i >= 0 && i+1 < grid.size() && grid[i+1][j] != grid[i][j]) until = scale*.8-tScale*.6;
    
    float teethShiftWidth = scale*.05;
    bool firstTime = false;
    for(; teethY < until; teethY += scale*.2*fastrandtoothgenpos()+scale*.05) {
        if(teethOffset >= scale*.3) teethOffset = scale*.1;
        teethOffset += scale*.1;
        //ofDrawRectangle(0,teethY,scale*.2,scale*.1);
        //fastrandtoothgen()*scale*.5;
        //int insertID = fastrandtoothgenseed;

        float teethWidth = scale*.1+scale*.3*fastrandtoothgenpos(), teethLength = fastrandtoothgenpos() * scale*.4 + scale*.1;
        float teethShift = teethShiftWidth*fastrandtoothgennegpos();
        
        //if(leftteethDP.count(insertID) == 0) {
            ofPath path;
            path.setHexColor(0xFFFFFF);
            path.setFilled(true);
            path.moveTo(0,teethY);
        
            if(!firstTime) teethShift -= teethShiftWidth*fastrandtoothgenpos();
            path.bezierTo(teethLength, teethY-teethShiftWidth+teethShift, teethLength, teethY+teethWidth+teethWidth+teethShift, 0, teethY+teethWidth);
            path.lineTo(0,teethY);
        //    leftteethDP[insertID] = path;
        //}
        
        
        teethY += teethWidth;
        if(teethY + teethShift< until) path.draw();
        firstTime = true;
    }
    
    //Think about how far the teeth go.
    if(i==0) for(int k = -1; position.getTop() + (k+1)*scale >= 0; --k) {
        ofTranslate(0,-scale);
        drawMonsterTeethLeft(k,j,scale,tScale,grid, position);
    }
    if(i+1==grid.size()) for(int k = i+1; position.getTop() + (k-i-10)*scale < getHeight(); ++k) {
        ofTranslate(0,scale);
        drawMonsterTeethLeft(k,j,scale,tScale,grid, position);
    }
}



void drawMonsterTeethRight(int i, int j, float scale, float tScale, deque<deque<int> > & grid, ofRectangle & position) {
    for(int k = 0; j-2 >= 0 && k < grid.size(); ++k) if(getCellType(grid[k][j-2]) == GRAVITYMONSTEREYE || getCellType(grid[k][j-2]) == GRAVITYMONSTERDEADEYE) {
        fastrandtoothgenseed = (1002*(k-i)) % 32767;
        break;
    }
    ofSetColor(255);
    float teethOffset = scale*.1*fastrandtoothgenpos()+scale*.01;//minsize
    float teethY = -scale*.1;
    if(i-1 >= 0 && i < grid.size() && grid[i-1][j] != grid[i][j]) teethY = scale *.15;
    
    float until = scale*.8;
    if(i >= 0 && i+1 < grid.size() && grid[i+1][j] != grid[i][j]) until = scale*.8-tScale*.6;
    
    float teethShiftWidth = scale*.05;
    bool firstTime = true;
    for(; teethY < until; teethY += scale*.2*fastrandtoothgenpos()+scale*.05) {
        if(teethOffset >= scale*.3) teethOffset = scale*.1;
        teethOffset += scale*.1;
        //ofDrawRectangle(0,teethY,scale*.2,scale*.1);
        //fastrandtoothgen()*scale*.5;
        ofPath path;
        path.setHexColor(0xFFFFFF);
        path.setFilled(true);
        path.moveTo(scale*.8,teethY);
        
        float teethWidth = scale*.1+scale*.3*fastrandtoothgenpos(), teethLength = fastrandtoothgenpos() * scale*.4 + scale*.1;
        float teethShift = teethShiftWidth*fastrandtoothgennegpos();
        if(!firstTime) teethShift -= teethShiftWidth*fastrandtoothgenpos();
        path.bezierTo(scale*.8-teethLength, teethY-teethShiftWidth+teethShift, scale*.8-teethLength, teethY+teethWidth+teethWidth+teethShift, scale*.8, teethY+teethWidth);
        path.lineTo(scale*.8,teethY);
        teethY += teethWidth;
        if(teethY + teethShift< until) path.draw();
        firstTime = true;
    }
    
    //ADDITIONALLY DRAW BROWN BACKGROUND
    ofSetColor(scheme.colorGRAVITYMONSTER);
    ofFill();
    ofDrawRectangle(scale*.8,0,scale*.8,scale*1.2);
    
    //Think about how far the teeth go.
    if(i==0) for(int k = -1; position.getTop() + (k+1)*scale >= 0; --k) {
        ofTranslate(0,-scale);
        drawMonsterTeethRight(k,j,scale,tScale,grid, position);
    }
    if(i+1==grid.size()) for(int k = i+1; position.getTop() + (k-i-10)*scale < getHeight(); ++k) {
        ofTranslate(0,scale);
        drawMonsterTeethRight(k,j,scale,tScale,grid, position);
    }
}

void drawCellStroke(int o, int p, float scale, float tScale, deque<deque<int> > & grid) {
    ofNoFill();
    
    bool t = (o == 0 || grid[o-1][p] != grid[o][p]);
    bool b = (o == grid.size() - 1 || grid[o+1][p] != grid[o][p]);
    bool l = (p == 0 || grid[o][p-1] != grid[o][p]);
    bool r = (p == grid[0].size() - 1 || grid[o][p+1] != grid[o][p]);
    
    /*stack<int> antiAliasingQueue;
     antiAliasingQueue.push(0);
     //antiAliasingQueue.push(LINE_WIDTH);
     ofSetColor(0, 0, 0);
     while(!antiAliasingQueue.empty()) {
     int i = antiAliasingQueue.top();
     antiAliasingQueue.pop();
     if(t) {
     if(l && tryArcing) ofDrawCurve(scale - tScale, i, tScale, 0, 0, tScale, i, scale - tScale);
     if(l && !tryArcing) ofDrawLine(tScale, i, i, tScale);
     if(r && tryArcing) ofDrawCurve(tScale, i, scale - tScale, 0, scale - 0, tScale, scale - i, scale - tScale);
     if(r && !tryArcing) ofDrawLine(scale - tScale, i, scale - i, tScale);
     }
     if(b) {
     if(l && tryArcing) ofDrawCurve(scale - tScale, scale - i, tScale, scale - 0, 0, scale - tScale, i, tScale);
     if(l && !tryArcing) ofDrawLine(tScale, scale - i, i, scale - tScale);
     if(r && tryArcing) ofDrawCurve(tScale, scale - i, scale - tScale, scale - 0, scale - 0, scale - tScale, scale - i, tScale);
     if(r && !tryArcing) ofDrawLine(scale - tScale, scale - i, scale - i, scale - tScale);
     }
     }*/
    
    ofSetLineWidth(1);
    //ofEnableSmoothing();
    
    for(int i = 1; i < LINE_WIDTH+2; ++i) {
        ofDisableSmoothing();
        /*
         glDisable(GL_LINE_SMOOTH);
         glDisable(GL_POINT_SMOOTH);
         glDisable(GL_DITHER);
         glDisable(GL_POINT_SMOOTH);
         glDisable(GL_LINE_SMOOTH);
         glDisable(GL_POLYGON_SMOOTH);
         glHint(GL_POINT_SMOOTH, GL_DONT_CARE);
         glHint(GL_LINE_SMOOTH, GL_DONT_CARE);
         glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
         #define GL_MULTISAMPLE_ARB 0x809D
         glDisable( GL_MULTISAMPLE_ARB);*/
        int edgeConst = 1;
        int lE = 3; //lineExtension
        
        if(t) {
            ofDrawLine(tScale - edgeConst, i, scale - tScale + edgeConst, i);
            if(l && tryArcing) ofDrawCurve(scale - tScale, i, tScale, i, i, tScale, i, scale - tScale);
            if(l && !tryArcing) ofDrawLine(tScale, i, i, tScale);
            if(!l) ofDrawLine(0, i, scale - tScale, i);
            if(r && tryArcing) ofDrawCurve(tScale, i, scale - tScale, i, scale - i, tScale, scale - i, scale - tScale);
            if(r && !tryArcing) ofDrawLine(scale - tScale, i, scale - i, tScale);
            if(!r) ofDrawLine(tScale, i, scale, i);
            
        }
        if(l) {
            ofDrawLine(i, scale - tScale + edgeConst, i, tScale - edgeConst);
            if(!t) ofDrawLine(i, tScale, i, -LINE_WIDTH);
            if(!b) ofDrawLine(i, scale - tScale, i, scale + LINE_WIDTH+lE - edgeConst);
        }
        if(b) {
            ofDrawLine(scale - tScale + edgeConst, scale - i, tScale - edgeConst, scale - i);
            if(l && tryArcing) ofDrawCurve(scale - tScale, scale - i, tScale, scale - i, i, scale - tScale, i, tScale);
            if(l && !tryArcing) ofDrawLine(tScale, scale - i, i, scale - tScale);
            if(!l) ofDrawLine(0, scale - i, tScale, scale - i);
            if(r && tryArcing) ofDrawCurve(tScale, scale - i, scale - tScale, scale - i, scale - i, scale - tScale, scale - i, tScale);
            if(r && !tryArcing) ofDrawLine(scale - tScale, scale - i, scale - i, scale - tScale);
            if(!r) ofDrawLine(scale - tScale, scale - i, scale, scale - i);
        }
        if(r) {
            ofDrawLine(scale - i, tScale - edgeConst, scale - i, scale - tScale + edgeConst);
            if(!t) ofDrawLine(scale - i, tScale, scale - i, -LINE_WIDTH);
            if(!b) ofDrawLine(scale - i, scale - tScale, scale - i, scale + LINE_WIDTH+lE - edgeConst);
        }
    }
    
    
    
    /*
     glEnable(GL_LINE_SMOOTH);
     glEnable(GL_POINT_SMOOTH);
     ofEnableSmoothing();
     glEnable(GL_DITHER);
     glEnable(GL_POINT_SMOOTH);
     glEnable(GL_LINE_SMOOTH);
     glEnable(GL_POLYGON_SMOOTH);
     //glHint(GL_POINT_SMOOTH, GL_CARE);
     //glHint(GL_LINE_SMOOTH, GL_CARE);
     //glHint(GL_POLYGON_SMOOTH_HINT, GL_CARE);
     #define GL_MULTISAMPLE_ARB 0x809D
     glEnable( GL_MULTISAMPLE_ARB) ;
     
     
     for(int i = 0; i < LINE_WIDTH; ++i) {
     if(t) {
     ofDrawLine(tScale - 1, i, scale - tScale + 1, i);
     if(l && tryArcing) ofDrawCurve(scale - tScale, i, tScale, i, i, tScale, i, scale - tScale);
     if(l && !tryArcing) ofDrawLine(tScale, i, i, tScale);
     if(!l) ofDrawLine(0, i, scale - tScale, i);
     if(r && tryArcing) ofDrawCurve(tScale, i, scale - tScale, i, scale - i, tScale, scale - i, scale - tScale);
     if(r && !tryArcing) ofDrawLine(scale - tScale, i, scale - i, tScale);
     if(!r) ofDrawLine(tScale, i, scale, i);
     
     }
     if(l) {
     ofDrawLine(i, scale - tScale + 1, i, tScale - 1);
     if(!t) ofDrawLine(i, tScale, i, -LINE_WIDTH);
     if(!b) ofDrawLine(i, scale - tScale, i, scale + LINE_WIDTH - 1);
     }
     if(b) {
     ofDrawLine(scale - tScale + 1, scale - i, tScale - 1, scale - i);
     if(l && tryArcing) ofDrawCurve(scale - tScale, scale - i, tScale, scale - i, i, scale - tScale, i, tScale);
     if(l && !tryArcing) ofDrawLine(tScale, scale - i, i, scale - tScale);
     if(!l) ofDrawLine(0, scale - i, tScale, scale - i);
     if(r && tryArcing) ofDrawCurve(tScale, scale - i, scale - tScale, scale - i, scale - i, scale - tScale, scale - i, tScale);
     if(r && !tryArcing) ofDrawLine(scale - tScale, scale - i, scale - i, scale - tScale);
     if(!r) ofDrawLine(scale - tScale, scale - i, scale, scale - i);
     }
     if(r) {
     ofDrawLine(scale - i, tScale - 1, scale - i, scale - tScale + 1);
     if(!t) ofDrawLine(scale - i, tScale, scale - i, -LINE_WIDTH);
     if(!b) ofDrawLine(scale - i, scale - tScale, scale - i, scale + LINE_WIDTH - 1);
     }
     }
     
     
     */
    //ofEnableSmoothing();
    //ofFill();
    /*
     ofSetColor(0, 0, 0);
     for(float i = LINE_WIDTH * 1.5; i >= LINE_WIDTH; i-=0.25) {
     if(t) {
     if(l && tryArcing) ofDrawCurve(scale - tScale, i, tScale, 0, 0, tScale, i, scale - tScale);
     if(l && !tryArcing) ofDrawLine(tScale, i, i, tScale);
     if(r && tryArcing) ofDrawCurve(tScale, i, scale - tScale, 0, scale - 0, tScale, scale - i, scale - tScale);
     if(r && !tryArcing) ofDrawLine(scale - tScale, i, scale - i, tScale);
     }
     if(b) {
     if(l && tryArcing) ofDrawCurve(scale - tScale, scale - i, tScale, scale - 0, 0, scale - tScale, i, tScale);
     if(l && !tryArcing) ofDrawLine(tScale, scale - i, i, scale - tScale);
     if(r && tryArcing) ofDrawCurve(tScale, scale - i, scale - tScale, scale - 0, scale - 0, scale - tScale, scale - i, tScale);
     if(r && !tryArcing) ofDrawLine(scale - tScale, scale - i, scale - i, scale - tScale);
     }
     }
     ofNoFill();
     */
}

void drawCornerLight(int o, int p, int scale, int tScale, deque<deque<int> > & grid) {
    ofDisableSmoothing();
    
    /*glDisable(GL_LINE_SMOOTH);
     glDisable(GL_POINT_SMOOTH);
     ofDisableSmoothing();
     glDisable(GL_DITHER);
     glDisable(GL_POINT_SMOOTH);
     glDisable(GL_LINE_SMOOTH);
     glDisable(GL_POLYGON_SMOOTH);
     glHint(GL_POINT_SMOOTH, GL_DONT_CARE);
     glHint(GL_LINE_SMOOTH, GL_DONT_CARE);
     glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
     #define GL_MULTISAMPLE_ARB 0x809D
     glDisable( GL_MULTISAMPLE_ARB) ;*/
    ofFill();
    bool r = (p == grid[0].size() - 1 || grid[o][p+1] != grid[o][p]);
    bool t = (o == 0 || grid[o-1][p] != grid[o][p]);
    if(t && r && tryArcing) ofDrawCurve(-10*tScale, -1, scale - (2*tScale), -1, scale + 1, tScale * 2, scale + 1, 10*tScale);
}

void recheckGrid() {
    if(movements.size() == 0) {
        grid = moveGrid;
        eyeGrid = moveEyeGrid;
    }
}



//DO COPY THE DISPLAY MORE THAN ONCE!
void displayLevel() {
    float scaleY = (getHeight() * 1.) / (MAX(grid.size() + 2, MIN_CELL_SIZE) * 1.);
    float scaleX = (getWidth() * 1.) / (MAX(grid[0].size() + 2, MIN_CELL_SIZE) * 1.);
    float scale = MIN(scaleY, scaleX);
    float tScale = scale / 5.;
    LINE_WIDTH = MAX(1, scale / 20.);
    vector<vector<ofRectangle> > rects(grid.size(), vector<ofRectangle>(grid[0].size()));
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(movements.size() == 0) rects[i][j] = calculatePosition(i, j, grid.size(), grid[i].size());
            else rects[i][j] = movements.front().calculatePosition(i, j);
        }
    }
    ofFill();
    
    generateLookAt(eyeGrid);
    
    //Draw the background of the monster.
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH || getCellType(grid[i][j]) == GRAVITYMONSTEREYE || getCellType(grid[i][j]) == GRAVITYMONSTERDEADEYE) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                ofPushMatrix();
                if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH) ofTranslate(-scale*2,0);
                ofSetColor(scheme.colorGRAVITYMONSTER);
                drawCellMonsterFill(i, j, scale, tScale, grid, LEFT);
                ofPopMatrix();
                ofPopMatrix();
            }
        }
    }
    
    //Draw the monster (beside right teeth overlay)
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH || getCellType(grid[i][j]) == GRAVITYMONSTEREYE || getCellType(grid[i][j]) == GRAVITYMONSTERDEADEYE) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                ofPushMatrix();
                if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH) ofTranslate(-scale*2,0);
                ofSetColor(scheme.colorGRAVITYMONSTER);
                if(getCellType(grid[i][j]) == GRAVITYMONSTEREYE) {
                    drawCellMonsterFill(i, j, scale, tScale, grid, LEFT);
                    drawMonsterEye(i,j,scale,tScale,grid);
                }
                else if(getCellType(grid[i][j]) == GRAVITYMONSTERDEADEYE) {
                    drawCellMonsterFill(i, j, scale, tScale, grid, LEFT);
                    drawMonsterEye(i,j,scale,tScale,grid);
                }
                else if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH) {
                    ofPushMatrix();
                    ofTranslate(0,scale*.1);
                    ofScale(2,1);
                    drawMonsterMouth(i,j,scale,tScale,grid,rects[i][j]);
                    drawMonsterTeethLeft(i,j,scale,tScale,grid,rects[i][j]);
                    ofPopMatrix();
                }
                ofPopMatrix();
                ofPopMatrix();
            }
        }
    }
    
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] != 0) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                cellType cT = getCellType(grid[i][j]);
                if(cT == PLAYER) {
                    ofSetColor(scheme.colorPLAYERUNSELECTED);//ofSetColor(255, 255, 0);
                    if(grid[i][j] == playerID) ofSetColor(scheme.colorPLAYERSELECTED);
                }
                else if(cT == ENEMY) ofSetColor(scheme.colorENEMY);//ofSetColor(255, 100, 0);
                else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMY); //ofSetColor(50, 50, 50);
                else if(cT == LOVE) ofSetColor(scheme.colorLOVE);
                
                if(cT == PLAYER || cT == ENEMY || cT == UNMOVABLE_ENEMY || cT == LOVE) drawCellFill(i, j, scale, tScale, grid);
                
                drawEyes(i, j, scale, tScale, eyeGrid);
                ofPopMatrix();
            }
            
        }
    }
    
    
    
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] != 0) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                //ofTranslate(scale*0.02, scale*0.02);
                cellType cT = getCellType(grid[i][j]);
                if(cT == ENEMY) ofSetColor(scheme.colorENEMYSTROKE);//ofSetColor(255, 0, 0);
                else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);//ofSetColor(0, 0, 0);
                else if(cT == LOVE) ofSetColor(scheme.colorLOVESTROKE);
                
                if(cT == ENEMY || cT == UNMOVABLE_ENEMY || cT == LOVE) drawCellStroke(i, j, scale, tScale, grid);
                ofPopMatrix();
            }
        }
    }
    
    
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH){
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                ofPushMatrix();
                ofTranslate(-scale*2,0);
                ofPushMatrix();
                ofTranslate(0,scale*.1);
                ofScale(2,1);
                drawMonsterTeethRight(i,j,scale,tScale,grid,rects[i][j]);
                ofPopMatrix();
                ofPopMatrix();
                ofPopMatrix();
            }
        }
    }
    
    
}




//local graphics DP
pair<vector<vector<ofRectangle> >, vector<vector<cellType> > > rectsDP; //TODO! Reset this on change of width, etc!
float scaleChange = -1; //In case any of the figures change size due to continous movement, redraw.

void switchRenderMode(RenderMode in) {
    if(beautifulGraphics) renderMode = FULL;
    else {
        renderMode = in;
        if(renderMode == PARTIAL) {
            rectsDP.first.clear(); rectsDP.second.clear();
            ofSetBackgroundAuto(false);
        } else if(renderMode == FULL) {
            ofSetBackgroundAuto(true);
        }
    }
}

void displayLevelWORefresh() {
    float scaleY = (getHeight() * 1.) / (MAX(grid.size() + 2, MIN_CELL_SIZE) * 1.);
    float scaleX = (getWidth() * 1.) / (MAX(grid[0].size() + 2, MIN_CELL_SIZE) * 1.);
    float scale = MIN(scaleY, scaleX);
    
    float tScale = scale / 5.;
    LINE_WIDTH = MAX(1, scale / 20.);
    vector<vector<ofRectangle> > rects(grid.size(), vector<ofRectangle>(grid[0].size()));
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(movements.size() == 0) rects[i][j] = calculatePosition(i, j, grid.size(), grid[i].size());
            else rects[i][j] = movements.front().calculatePosition(i, j);
        }
    }
    ofFill();
    
    assert(rects.size() > 0); //Cannot load an empty level.
    if(rectsDP.first.size() != rects.size() || rectsDP.first[0].size() != rects[0].size() || scale != scaleChange) {
        //Make sure everything is overwritten
        ofBackground(backgroundColor);
        //Make sure nothing is drawn with it
        vector<vector<ofRectangle> > rectsDPR = vector<vector<ofRectangle> >(rects.size(), vector<ofRectangle>(rects[0].size(),ofRectangle(-1,-1,-1,-1)));
        vector<vector<cellType> > rectsDPC = vector<vector<cellType> >(rects.size(), vector<cellType>(rects[0].size(),AIR));
        rectsDP = {rectsDPR, rectsDPC};
        scaleChange = scale;
    }
    
    //Generate eye positions
    generateLookAt(eyeGrid);
    
    
    //Draw blocks and eyes, etc.
    set<pair<int,int> > needToBeDrawn;
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(rectsDP.first[i][j].getTopLeft() == rects[i][j].getTopLeft() && rectsDP.second[i][j] == getCellType(grid[i][j])) {}
            else {
                //In case the block moved, update all neighboring tiles!
                // 0
                //123
                // 4
                
                ofSetColor(scheme.colorBACKGROUND);
                ofDrawRectangle(calculatePosition(i, j, grid.size(), grid[i].size()));
                
                //TODO: Perhaps lessen the number of draws here, since gravity blocks are loaded correctly.
                if(j + 1 < grid[i].size() && getCellType(grid[i][j+1]) == GRAVITYMONSTERMOUTH || j + 2 < grid[i].size() && getCellType(grid[i][j+2]) == GRAVITYMONSTERMOUTH) {
                    for(int k = 0; k <= 0xF+1; ++k) {
                        //  2DE
                        //  39A
                        //01478
                        //  5BC
                        //  6FG
                        int ti = k == 2||k==0xD||k==0xE ? i - 2 : k == 3||k==9||k==0xA ? i - 1 : k == 5||k==0xB||k==0xC ? i + 1 : k == 6||k==0xF||k==0x10 ? i + 2 :  i;
                        int tj = k == 0 ? j - 2 : k == 1 ? j - 1 : k == 7||k==9||k==0xB||k==0xD||k==0xF ? j + 1 : k == 8||k==0xA||k==0xB||k==0xE||k==0x10 ? j + 2 : j;
                        
                        if(ti >= 0 && ti < grid.size() && tj >= 0 && tj < grid[ti].size() && grid[ti][tj] != 0) {
                            needToBeDrawn.insert({ti,tj});
                        }
                    }
                }
                else {
                    for(int k = 0; k <= 4; ++k) {
                        int ti = k == 1 ? i - 1 : k == 3 ? i + 1 : i; //for k <= 4
                        int tj = k == 0 ? j - 1 : k == 4 ? j + 1 : j;
                        // 0
                        //123
                        // 4
                        
                        //ofDrawRectangle(0,0,scale,scale);
                        if(ti >= 0 && ti < grid.size() && tj >= 0 && tj < grid[ti].size() && grid[ti][tj] != 0) {
                            needToBeDrawn.insert({ti,tj});
                        }
                    }
                }
                rectsDP.first[i][j] = rects[i][j];
                rectsDP.second[i][j] = getCellType(grid[i][j]);
            }
        }
    }
    
    //Draw the background of the monster.
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if((getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH || getCellType(grid[i][j]) == GRAVITYMONSTEREYE || getCellType(grid[i][j]) == GRAVITYMONSTERDEADEYE) && needToBeDrawn.count({i,j}) != 0) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                ofPushMatrix();
                if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH) ofTranslate(-scale*2,0);
                ofSetColor(scheme.colorGRAVITYMONSTER);
                drawCellMonsterFill(i, j, scale, tScale, grid, LEFT);
                ofPopMatrix();
                ofPopMatrix();
            }
        }
    }
    
    //Draw the monster (beside right teeth overlay)
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if((getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH || getCellType(grid[i][j]) == GRAVITYMONSTEREYE || getCellType(grid[i][j]) == GRAVITYMONSTERDEADEYE) && needToBeDrawn.count({i,j}) != 0) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                ofPushMatrix();
                if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH) ofTranslate(-scale*2,0);
                ofSetColor(scheme.colorGRAVITYMONSTER);
                if(getCellType(grid[i][j]) == GRAVITYMONSTEREYE) {
                    drawCellMonsterFill(i, j, scale, tScale, grid, LEFT);
                    drawMonsterEye(i,j,scale,tScale,grid);
                }
                else if(getCellType(grid[i][j]) == GRAVITYMONSTERDEADEYE) {
                    drawCellMonsterFill(i, j, scale, tScale, grid, LEFT);
                    drawMonsterEye(i,j,scale,tScale,grid);
                }
                else if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH) {
                    ofPushMatrix();
                    ofTranslate(0,scale*.1);
                    ofScale(2,1);
                    drawMonsterMouth(i,j,scale,tScale,grid,rects[i][j]);
                    drawMonsterTeethLeft(i,j,scale,tScale,grid,rects[i][j]);
                    ofPopMatrix();
                }
                ofPopMatrix();
                ofPopMatrix();
            }
        }
    }
    
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] != 0 && needToBeDrawn.count({i,j}) != 0){
                int ti = i, tj = j;
                
                needToBeDrawn.insert({ti,tj});
                ofPushMatrix();
                ofTranslate(rects[ti][tj].getTopLeft());
                
                cellType cT = getCellType(grid[ti][tj]);
                if(cT == PLAYER) {
                    ofSetColor(scheme.colorPLAYERUNSELECTED);//ofSetColor(255, 255, 0);
                    if(grid[ti][tj] == playerID) ofSetColor(scheme.colorPLAYERSELECTED);
                }
                else if(cT == ENEMY) ofSetColor(scheme.colorENEMY);//ofSetColor(255, 100, 0);
                else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMY); //ofSetColor(50, 50, 50);
                else if(cT == LOVE) ofSetColor(scheme.colorLOVE);
                
                /*if(cT == GRAVITYMONSTEREYE) {
                    ofPushMatrix();
                    ofTranslate(-scale*2,0);
                    drawCellMonsterFill(ti, tj, scale, tScale, grid, LEFT);
                    drawMonsterEye(ti,tj,scale,tScale,grid);
                    ofPopMatrix();
                }*/
                if(cT == PLAYER || cT == ENEMY || cT == UNMOVABLE_ENEMY || cT == LOVE) drawCellFill(ti, tj, scale, tScale, grid);
                
                drawEyes(ti, tj, scale, tScale, eyeGrid);
                
                /*
                 if(grid[ti][tj] != 0) {
                 //ofTranslate(rects[ti][tj].getTopLeft());
                 //ofTranslate(scale*0.02, scale*0.02);
                 //cellType cT = getCellType(grid[ti][tj]);
                 if(cT == ENEMY) ofSetColor(scheme.colorENEMYSTROKE);//ofSetColor(255, 0, 0);
                 else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);//ofSetColor(0, 0, 0);
                 
                 if(cT == ENEMY || cT == UNMOVABLE_ENEMY) drawCellStroke(ti, tj, scale, tScale, grid);
                 }*/
                
                ofPopMatrix();
            }
        }
    }
    
    //Draw cell stroke
    //No idea why this can't be optimized
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] != 0 && needToBeDrawn.count({i,j}) != 0){
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                //ofTranslate(scale*0.02, scale*0.02);
                cellType cT = getCellType(grid[i][j]);
                if(cT == ENEMY) ofSetColor(scheme.colorENEMYSTROKE);//ofSetColor(255, 0, 0);
                else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);//ofSetColor(0, 0, 0);
                else if(cT == LOVE) ofSetColor(scheme.colorLOVESTROKE);

                
                if(cT == ENEMY || cT == UNMOVABLE_ENEMY || cT == LOVE) drawCellStroke(i, j, scale, tScale, grid);
                ofPopMatrix();
            }
        }
    }
    
    
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(getCellType(grid[i][j]) == GRAVITYMONSTERMOUTH && needToBeDrawn.count({i,j}) != 0){
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                ofPushMatrix();
                ofTranslate(-scale*2,0);
                ofPushMatrix();
                ofTranslate(0,scale*.1);
                ofScale(2,1);
                drawMonsterTeethRight(i,j,scale,tScale,grid,rects[i][j]);
                ofPopMatrix();
                ofPopMatrix();
                ofPopMatrix();
            }
        }
    }
    
    
    needToBeDrawn.clear();
}




void displayPencil(bool selected) {
    
    ofPushMatrix();
    ofScale(min(getWidth(),getHeight())/750.,min(getWidth(),getHeight())/750.,min(getWidth(),getHeight())/750.);
    ofFill();
    ofSetColor((int)0x0f,(int)0x8d,(int)0x00);
    ofDrawEllipse(-20, 10, 45, 45);
    ofSetColor(0,255,0);
    if(selected) ofTranslate(0,3);
    ofDrawEllipse(-20, 5, 45, 45);
    
    ofPushMatrix();
    ofTranslate(-20,5); //do center rotation
    ofRotate(-45);
    ofTranslate(20,-5); //undo center rotation
    
    ofSetColor((int)0xc8,(int)0xff,(int)0x00);
    ofDrawEllipse(-20,5,45,20);
    
    //Pencil body
    ofSetColor((int)0xec,(int)0xf7,(int)0xc3);
    ofFill();
    ofBeginShape();
    ofVertex(0,0);
    ofVertex(-30,0);
    ofVertex(-30,10);
    ofVertex(0,10);
    ofEndShape();
    
    //Pencil head
    ofSetColor(255,255,255);
    ofFill();
    ofBeginShape();
    ofVertex(-30,0);
    ofVertex(-40,5);
    ofVertex(-30,10);
    ofEndShape();
    
    //Pencil point
    ofSetColor(0);
    ofFill();
    ofBeginShape();
    ofVertex(-35,2.5);
    ofVertex(-40,5);
    ofVertex(-35,7.5);
    ofEndShape();
    
    
    //Pencil head frame
    ofSetColor(0);
    ofNoFill();
    ofVertex(-35,2.5);
    ofVertex(-40,5);
    ofVertex(-35,7.5);
    ofBeginShape();
    ofEndShape();
    
    
    ofSetColor(0,0,0);
    ofNoFill();
    for(int i = 0; i < 3; ++i) {
        ofPushMatrix();
        ofTranslate(0,(10./3)*i);
        ofBeginShape();
        ofVertex(0,0);
        ofVertex(-30,0);
        ofVertex(-30,10./3);
        ofVertex(0,10./3);
        ofVertex(0,0);
        ofEndShape();
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopMatrix();
}

/*
 SHAPES
 ofBeginShape();
 ofCurveVertex(tScale, 0);
 ofCurveVertex(scale - tScale, 0);
 ofCurveVertex(scale, 0);
 ofCurveVertex(scale, tScale);
 ofCurveVertex(scale, scale - tScale);
 ofCurveVertex(scale - tScale, scale);
 ofCurveVertex(tScale, scale);
 ofCurveVertex(0, scale - tScale);
 ofCurveVertex(0, tScale);
 ofCurveVertex(tScale, 0);
 ofEndShape();
 
 */

#endif
