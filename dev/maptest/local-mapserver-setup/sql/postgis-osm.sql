-- optional, makes it easier to wrap place names
update osm_point set name = replace(name,'-',' ');

-- grant our user access to the data
grant SELECT on osm_line to "pgis";
grant SELECT on osm_point to "pgis";
grant SELECT on osm_polygon to "pgis";

-- correct a few common typos
update osm_line set tunnel='yes' where tunnel='true';
update osm_line set tunnel='no' where tunnel='false';
update osm_line set tunnel='yes' where tunnel='yel';
update osm_line set bridge='yes' where bridge='true';
update osm_line set oneway='yes' where oneway='Yes';
update osm_line set oneway='yes' where oneway='true';
update osm_line set oneway='yes' where oneway='1';


-- make do the happen primary keys for great justice
alter table osm_line add primary key (osm_id);
alter table osm_polygon add primary key (osm_id);
alter table osm_point add primary key (osm_id);
alter table osm_roads add primary key (osm_id);


-- rename one of the columns to make it easier to write mapserver expressions
alter table osm_polygon rename column "natural" to nature;

-- create a few indexes on the data for speedier access
create index osm_polygon_building_idx on osm_polygon(building);
create index osm_polygon_amenity_idx on osm_polygon(amenity);
create index osm_polygon_landuse_idx on osm_polygon(landuse);
create index osm_line_highway_idx on osm_line(highway);
create index osm_line_aeroway_idx on osm_line(aeroway);
create index osm_line_railway_idx on osm_line(railway);
create index osm_line_bridge_idx on osm_line(bridge);
create index osm_polygon_leisure_idx on osm_polygon(leisure);
create index osm_polygon_aeroway_idx on osm_polygon(aeroway);
create index osm_polygon_waterway_idx on osm_polygon(waterway);
create index osm_polygon_natural_idx on osm_polygon(nature);
create index osm_point_place_idx on osm_point(place);
create index osm_line_zorder_idx on osm_line(z_order);
create index osm_roads_name_idx on osm_roads(name);
