-- Add the Spherical Mercator (900913) projection to the database
INSERT INTO spatial_ref_sys (srid, auth_name, auth_srid, srtext, proj4text)
VALUES (900913, 'spatialreference.org', 900913,
  'PROJCS["unnamed",GEOGCS["unnamed ellipse",DATUM["unknown",
   SPHEROID["unnamed",6378137,0]],PRIMEM["Greenwich",0],
   UNIT["degree",0.0174532925199433]],PROJECTION["Mercator_2SP"],
   PARAMETER["standard_parallel_1",0],PARAMETER["central_meridian",0],
   PARAMETER["false_easting",0],PARAMETER["false_northing",0],
   UNIT["Meter",1],
   EXTENSION["PROJ4","+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0
   +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs"]]',
   '+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0
   +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs');

-- optional, makes it easier to wrap place names
update planet_osm_point set name = replace(name,'-',' ');

-- grant our user access to the data
grant SELECT on planet_osm_line to "gis";
grant SELECT on planet_osm_point to "gis";
grant SELECT on planet_osm_polygon to "gis";

-- correct a few common typos
update planet_osm_line set tunnel='yes' where tunnel='true';
update planet_osm_line set tunnel='no' where tunnel='false';
update planet_osm_line set tunnel='yes' where tunnel='yel';
update planet_osm_line set bridge='yes' where bridge='true';
update planet_osm_line set oneway='yes' where oneway='Yes';
update planet_osm_line set oneway='yes' where oneway='true';
update planet_osm_line set oneway='yes' where oneway='1';


-- make do the happen primary keys for great justice
alter table planet_osm_line add primary key (osm_id);
alter table planet_osm_polygon add primary key (osm_id);
alter table planet_osm_point add primary key (osm_id);
alter table planet_osm_roads add primary key (osm_id);


-- rename one of the columns to make it easier to write mapserver expressions
alter table planet_osm_polygon rename column "natural" to nature;

-- create a few indexes on the data for speedier access
create index planet_osm_polygon_building_idx on planet_osm_polygon(building);
create index planet_osm_polygon_amenity_idx on planet_osm_polygon(amenity);
create index planet_osm_polygon_landuse_idx on planet_osm_polygon(landuse);
create index planet_osm_line_highway_idx on planet_osm_line(highway);
create index planet_osm_line_aeroway_idx on planet_osm_line(aeroway);
create index planet_osm_line_railway_idx on planet_osm_line(railway);
create index planet_osm_line_bridge_idx on planet_osm_line(bridge);
create index planet_osm_polygon_leisure_idx on planet_osm_polygon(leisure);
create index planet_osm_polygon_aeroway_idx on planet_osm_polygon(aeroway);
create index planet_osm_polygon_waterway_idx on planet_osm_polygon(waterway);
create index planet_osm_polygon_natural_idx on planet_osm_polygon(nature);
create index planet_osm_point_place_idx on planet_osm_point(place);
create index planet_osm_line_zorder_idx on planet_osm_line(z_order);
create index planet_osm_roads_name_idx on planet_osm_roads(name);
