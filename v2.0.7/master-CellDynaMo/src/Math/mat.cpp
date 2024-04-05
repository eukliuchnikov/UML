/*
 *most used formulas
 *
 *  Created on: Mar 15, 2018
 *	Edited on:	Mar 30, 2019
 *      Author: kliuchnikov
 */

#include "mat.h"

float myDistance(float3 ri, float3 rj){
	return sqrt(pow(ri.x - rj.x, 2) + pow(ri.y - rj.y, 2) + pow(ri.z - rj.z, 2));
}

float length(float3 r){
	return sqrt(pow(r.x, 2) + pow(r.y, 2) + pow(r.z, 2));
}

float scalar(float3 ri, float3 rj){
	return (ri.x*rj.x + ri.y*rj.y + ri.z*rj.z); 
}

int computeGamma(float r){
	return 6*M_PI*VISCOSITY*r;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************************************************************************************************************//
//take index of cell and return coords of its center in nm (local coordinates)
//**************************************************************************************************************************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float3 get_coord(int3 cell){
	float3 dr;
	dr.x = config.sv_size1*(cell.x - 1.0) + config.sv_size1/2.0;
	dr.y = config.sv_size1*(cell.y - 1.0) + config.sv_size1/2.0;
	dr.z = config.sv_size1*(cell.z - 1.0) + config.sv_size1/2.0;
	return dr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************************************************************************************************************//
//take coords of cell (local) and return indx of cell
//**************************************************************************************************************************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int3 get_cell(float3 r){
	int3 cell_index;
	cell_index.x = floor(r.x/config.sv_size1) + 1;
	cell_index.y = floor(r.y/config.sv_size1) + 1;
	cell_index.z = floor(r.z/config.sv_size1) + 1;
	return cell_index;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************************************************************************************************************//
//convert coords of cells (local) into indx
//**************************************************************************************************************************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int COORintoARRAY(int x, int y, int z){
	int N;
	if (x <= num_x_cell && y <= num_y_cell && z <= num_z_cell && x > 0 && y > 0 && z > 0){	
		N = num_x_cell*num_y_cell*(z - 1) + (y - 1)*num_x_cell + x;
	}
	else{
		printf("Wrong ccordinates! (%d-%d-%d)\n", x, y, z);
		DCD_step(dcd);
		exit(0);
	}
	N = N - 1;
	return N;	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************************************************************************************************************//
//convert indx of cells into coords (local)
//**************************************************************************************************************************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int3 ARRAYintoCOOR(int N){
	int3 coor;
	N = N + 1;
	if (N > 0 && N < num_x_cell*num_y_cell*num_z_cell){
		if (N % int(num_x_cell) == 0){
			coor.x = 1;
		}
		else	{	
			coor.x = N - floor(N/num_x_cell)*num_x_cell;
		}		
		if (((int) floor(N/num_x_cell) + 1) % int(num_y_cell) == 0){
			coor.y = num_y_cell;
		}
		else{
			coor.y = (((int) floor(N/num_x_cell) + 1)% int(num_y_cell));		
		}
		coor.z = (N - (coor.y - 1)*num_x_cell - coor.x)/(num_x_cell*num_y_cell) + 1;
	}
	return coor;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************************************************************************************************************//
//transfer of coordinate system from implicit layer to explicit layer
//**************************************************************************************************************************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float3 COORtransfer(float3 r){
	float3 r0; // coordinates in new coordinate system
	r0.x =  r.x - 0.5*float(XBOX);
	r0.y =  r.y - 0.5*float(YBOX);
	r0.z =  r.z - 0.5*float(ZBOX);

	return r0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************************************************************************************************************//
//transfer of coordinate system from explicit layer to implicit layer
//**************************************************************************************************************************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float3 COORtransfer1(float3 r){
	float3 r0; // coordinates in new coordinate system
	r0.x =  r.x + 0.5*float(XBOX);
	r0.y =  r.y + 0.5*float(YBOX);
	r0.z =  r.z + 0.5*float(ZBOX);

	return r0;
}