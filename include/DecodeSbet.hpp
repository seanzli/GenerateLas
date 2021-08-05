/*
 * @Description: decode pos file
 * @Author: Sean
 * @Date: 2021-07-15 21:11:21
 * @LastEditTime: 2021-08-05 17:23:28
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

#include <string>
#include <vector>
#include <cstdio>

#include "StructDef.h"
//#include "Coordinate.hpp"
#include "CoordinateConvert.hpp"

class DecodePosFile {
public:
    DecodePosFile(Coordinate::Convert* p) : mp_coord(p) {}
    virtual ~DecodePosFile() {}
    virtual void decodePos(const std::string& pos_file, std::vector<Traj>& out) {}
    Coordinate::Convert* mp_coord = nullptr;
protected:
    //Coordinate* mp_coord = Coordinate::instance(EllipBuilder(WGS84));
private:
};

class DecodeSbetFile : public DecodePosFile {
public:
    DecodeSbetFile(Coordinate::Convert* p) : DecodePosFile(p) {}
    virtual ~DecodeSbetFile() {}

    virtual void decodePos(const std::string& pos_file, std::vector<Traj>& out) {
        VLOG(3) << "Pos file type = SBET\n";
        std::vector<SbetEntry> tmp;
        decodeSbet(pos_file, tmp);
        for (int i = 0; i < tmp.size(); ++i)
            out.push_back(convertSbet2Traj(tmp[i]));
        return;
    }

private:
#pragma pack(1)
	struct SbetEntry {
		double gpsTime;    	//GPS seconds of week
		double latitude;	//latitude in radians
		double longitude;	//longitude in radians
		double altitude;    //altitude
		double speed_x;    	//velocity in x direction
		double speed_y;    	//velocity in y direction
		double speed_z;    	//velocity in z direction
		double roll;    	//roll angle
		double pitch;    	//pitch angle
		double heading;    	//heading angle
		double wander;    	//wander
		double force_x;    	//force in x direction
		double force_y;    	//force in y direction
		double force_z;    	//force in z direction
		double angularRate_x; 	//angular rate in x direction
		double angularRate_y;  	//angular rate in y direction
		double angularRate_z;   //angular rate in z direction
	};
#pragma pack()
    void decodeSbet(const std::string& pos_file, std::vector<SbetEntry>& out) {
        FILE* fd = fopen(pos_file.c_str(), "rb");
        if (fd == nullptr) {
            return ; //can not open
        }

        out.clear();
        Traj cur_traj;
        SbetEntry cur_sbet_data;

        int bytesRead;
        double diff_time_n = 0.0, diff_time_p = 0.0;

        //read file
        do {
            bytesRead = fread(&cur_sbet_data, sizeof(SbetEntry),1, fd);
            if (bytesRead == 1)
                out.push_back(cur_sbet_data);
        } while (bytesRead > 0);

        fclose(fd);
    }
    Traj convertSbet2Traj(const SbetEntry& in) const {
        Traj out;
        out.gps_time = in.gpsTime;
        out.att.roll = in.roll;
        out.att.pitch = in.pitch;
        out.att.heading = in.heading - in.wander;
        out.pos = mp_coord->lla2ecef(LLA(in.latitude, in.longitude, in.altitude));
        out.val = VAL(in.speed_x, in.speed_y, in.speed_z);
        return out;
    }
};