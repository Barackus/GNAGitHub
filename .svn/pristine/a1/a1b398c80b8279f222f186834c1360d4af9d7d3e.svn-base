#ifndef VALVEMAP_H
#define VALVEMAP_H

#define WIDTH			1
#define HEIGHT			3
#define DEPTH			1
#define METER_TO_INCH	39.3700787f

#include <string>
#include <sstream>

template<int DIM> class DiscreteWorld;

/**
 * 
 **/
template<int DIM>
class ValveMap {
private:
	int _bid, _sid, _eid;
	std::stringstream _src;
	std::stringstream _fire;
	DiscreteWorld<DIM>* _world;
public:
	ValveMap(DiscreteWorld<DIM>*, int = 0);
	void save(const std::string&) const;
private:
	void brush(float, float, float, float, float, float, const std::string& = "DEV/GRAYGRID");
	void entity(const std::string&, const std::string&);
	void fire(float, float, float);
	void begin(void);
	void end(void);
};

/**
 * 
 **/
template<int DIM>
ValveMap<DIM>::ValveMap(DiscreteWorld<DIM>* world, int num_boids)
	:	_bid(0), _sid(0), _eid(0), _world(world) {
	cout << "Converting world to Valve Map Format... ";
	// Generate file header.
	begin();
	// Generate level geometry.
	float w = (float) world->width(), h = (float) world->height();
	float hw = w / 2, hh = h / 2;
	brush(-hw, -hh, -1, w, 1, h, "NATURE/GRASSFLOOR002A");
	for(int y = 0; y < h; ++y)
		for(int x = 0; x < w; ++x) {
			if(_world->get(x, int(h - y - 1)) == WALL)
				brush(x - hw, y - hh, 0, WIDTH, HEIGHT, DEPTH, "STONE/STONEWALL029A");
			if(_world->get(x, int(h - y - 1)) == DANGER)
				fire(x + 0.5f - hw, y + 0.5f - hh, 0);
		}
	brush(-hw, -hh, HEIGHT, w, 1, h, "TOOLS/TOOLSSKYBOX");
	_src << "}" << endl << _fire.str();
	_eid = _bid + _sid;
	// Generate boids.
	entity("gna_boidsystem", "boidsystem");
	for(int i = 0; i < num_boids; ++i) {
		stringstream ss;
		ss << "boid" << i;
		entity("gna_boid", ss.str());
	}
	// Generate file footer.
	end();
	cout << "Done." << endl;
}

/**
 * 
 **/
template<int DIM>
void ValveMap<DIM>::save(const std::string& filename) const {
	cout << "Saving world in VMF to: " << filename << "... ";
	ofstream out(filename);
	if(out.is_open())
		out << _src.str();
	out.close();
	cout << "Done." << endl;
}

/**
 * 
 **/
template<int DIM>
void ValveMap<DIM>::brush(float x, float y, float z, float w, float h, float d, const std::string& mat) {
	// Start brush.
	_src	<< "\tsolid" << endl
			<< "\t{" << endl
			<< "\t\t\"id\" \"" << ++_bid << "\"" << endl;
	// Generate sides.
	float x0, y0, z0, x1, y1, z1, x2, y2, z2;
	string u, v;
	float s = METER_TO_INCH;
	for(int i = 0; i < 6; ++i) {
		if(i == 0) {
			x0 = 0, y0 = 0, z0 = 1;
			x1 = 0, y1 = 1, z1 = 1;
			x2 = 1, y2 = 1, z2 = 1;
			u = "1 0 0", v = "0 -1 0";
		} else if(i == 1) {
			x0 = 0, y0 = 1, z0 = 0;
			x1 = 0, y1 = 0, z1 = 0;
			x2 = 1, y2 = 0, z2 = 0;
			u = "1 0 0", v = "0 -1 0";
		} else if(i == 2) {
			x0 = 0, y0 = 0, z0 = 0;
			x1 = 0, y1 = 1, z1 = 0;
			x2 = 0, y2 = 1, z2 = 1;
			u = "0 1 0", v = "0 0 -1";
		} else if(i == 3) {
			x0 = 1, y0 = 1, z0 = 0;
			x1 = 1, y1 = 0, z1 = 0;
			x2 = 1, y2 = 0, z2 = 1;
			u = "0 1 0", v = "0 0 -1";
		} else if(i == 4) {
			x0 = 0, y0 = 1, z0 = 0;
			x1 = 1, y1 = 1, z1 = 0;
			x2 = 1, y2 = 1, z2 = 1;
			u = "1 0 0", v = "0 0 -1";
		} else if(i == 5) {
			x0 = 1, y0 = 0, z0 = 0;
			x1 = 0, y1 = 0, z1 = 0;
			x2 = 0, y2 = 0, z2 = 1;
			u = "1 0 0", v = "0 0 -1";
		}
		_src	<< "\t\tside" << endl
				<< "\t\t{" << endl
				<< "\t\t\t\"id\" \"" << ++_sid << "\"" << endl
				<< "\t\t\t\"plane\" \"("
					<< s * (x + x0 * w) << " " << s * (y + y0 * d) << " " << s * (z + z0 * h) << ") ("
					<< s * (x + x1 * w) << " " << s * (y + y1 * d) << " " << s * (z + z1 * h) << ") ("
					<< s * (x + x2 * w) << " " << s * (y + y2 * d) << " " << s * (z + z2 * h) << ")\"" << endl
				<< "\t\t\t\"material\" \"" << mat << "\"" << endl
				<< "\t\t\t\"uaxis\" \"[" << u << " 0] 0.25\"" << endl
				<< "\t\t\t\"vaxis\" \"[" << v << " 0] 0.25\"" << endl
				<< "\t\t\t\"rotation\" \"0\"" << endl
				<< "\t\t\t\"lightmapscale\" \"16\"" << endl
				<< "\t\t\t\"smoothing_groups\" \"0\"" << endl
				<< "\t\t}" << endl;
	}
	// End brush.
	_src	<< "\t\teditor" << endl
			<< "\t\t{" << endl
			<< "\t\t\t\"color\" \"100 255 100\"" << endl
			<< "\t\t\t\"visgroupshown\" \"1\"" << endl
			<< "\t\t\t\"visgroupautoshown\" \"1\"" << endl
			<< "\t\t}" << endl
			<< "\t}" << endl;
}

/**
 * 
 **/
template<int DIM>
void ValveMap<DIM>::entity(const std::string& type, const std::string& name) {
	_src	<< "entity" << endl
			<< "{" << endl
			<< "\t\"id\" \"" << ++_eid << "\"" << endl
			<< "\t\"classname\" \"" << type << "\"" << endl
			<< "\t\"targetname\" \"" << name << "\"" << endl
			<< "\t\"angles\" \"0 0 0\"" << endl
			<< "\t\"origin\" \"0 0 0\"" << endl
			<< "\teditor" << endl
			<< "\t{" << endl
			<< "\t\t\"color\" \"0 0 255\"" << endl
			<< "\t\t\"visgroupshown\" \"1\"" << endl
			<< "\t\t\"visgroupautoshown\" \"1\"" << endl
			<< "\t\t\"logicalpos\" \"[0 0]\"" << endl
			<< "\t}" << endl
			<< "}" << endl;
}

/**
 * 
 **/
template<int DIM>
void ValveMap<DIM>::fire(float x, float y, float z) {
	float s = METER_TO_INCH;
	_fire	<< "entity" << endl
			<< "{" << endl
			<< "\t\"id\" \"" << (++_bid) << "\"" << endl
			<< "\t\"classname\" \"env_fire\"" << endl
			<< "\t\"damagescale\" \"0.0\"" << endl
			<< "\t\"fireattack\" \"4\"" << endl
			<< "\t\"firesize\" \"128\"" << endl
			<< "\t\"health\" \"10\"" << endl
			<< "\t\"ignitionpoint\" \"32\"" << endl
			<< "\t\"spawnflags\" \"261\"" << endl
			<< "\t\"origin\" \"" << s * x << " " << s * y << " " << s * z << "\"" << endl
			<< "\teditor" << endl
			<< "\t{" << endl
			<< "\t\t\"color\" \"255 0 0\"" << endl
			<< "\t\t\"visgroupshown\" \"1\"" << endl
			<< "\t\t\"visgroupautoshown\" \"1\"" << endl
			<< "\t\t\"logicalpos\" \"[0 0]\"" << endl
			<< "\t}" << endl
			<< "}" << endl;
}

/**
 * 
 **/
template<int DIM>
void ValveMap<DIM>::begin(void) {
	_src	<< "versioninfo" << endl
			<< "{" << endl
			<< "\t\"editorversion\" \"400\"" << endl
			<< "\t\"editorbuild\" \"4715\"" << endl
			<< "\t\"mapversion\" \"1\"" << endl
			<< "\t\"formatversion\" \"100\"" << endl
			<< "\t\"prefab\" \"0\"" << endl
			<< "}" << endl
			<< "visgroups" << endl
			<< "{" << endl
			<< "}" << endl
			<< "viewsettings" << endl
			<< "{" << endl
			<< "\t\"bSnapToGrid\" \"1\"" << endl
			<< "\t\"bShowGrid\" \"1\"" << endl
			<< "\t\"bShowLogicalGrid\" \"0\"" << endl
			<< "\t\"nGridSpacing\" \"64\"" << endl
			<< "\t\"bShow3DGrid\" \"0\"" << endl
			<< "}" << endl
			<< "world" << endl
			<< "{" << endl
			<< "\t\"id\" \"1\"" << endl
			<< "\t\"mapversion\" \"1\"" << endl
			<< "\t\"classname\" \"worldspawn\"" << endl
			<< "\t\"detailmaterial\" \"detail/detailsprites\"" << endl
			<< "\t\"detailvbsp\" \"detail.vbsp\"" << endl
			<< "\t\"maxpropscreenwidth\" \"-1\"" << endl
			<< "\t\"skyname\" \"sky_day01_01\"" << endl;
}

/**
 * 
 **/
template<int DIM>
void ValveMap<DIM>::end(void) {
	float s = METER_TO_INCH;
	float w = s * _world->width(), h = s * _world->height();
	float hw = w * 0.5f, hh = h * 0.5f;
	_src << "entity" << endl
		<< "{" << endl
		<< "\t\"id\" \"" << (_bid + _sid) << "\"" << endl
		<< "\t\"classname\" \"info_player_start\"" << endl
		<< "\t\"angles\" \"0 0 0\"" << endl
		<< "\t\"origin\" \"0 0 0\"" << endl
		<< "\teditor" << endl
		<< "\t{" << endl
		<< "\t\t\"color\" \"0 255 0\"" << endl
		<< "\t\t\"visgroupshown\" \"1\"" << endl
		<< "\t\t\"visgroupautoshown\" \"1\"" << endl
		<< "\t\t\"logicalpos\" \"[0 0]\"" << endl
		<< "\t}" << endl
		<< "}" << endl
		<< "cameras" << endl
		<< "{" << endl
		<< "\t\"activecamera\" \"-1\"" << endl
		<< "}" << endl
		<< "cordon" << endl
		<< "{" << endl
		<< "\t\"mins\" \"(" << -hw << " " << -hh << " " << -s << ")\"" << endl
		<< "\t\"maxs\" \"(" << hw << " " << hh << " " << s * (HEIGHT + 1) << ")\"" << endl
		<< "\t\"active\" \"1\"" << endl
		<< "}" << endl;
}

#endif