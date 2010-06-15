CREATE OR REPLACE FUNCTION Z_GetRoadAtCoords (
	coordX FLOAT,
	coordY FLOAT
) RETURNS VARCHAR(2048)AS $$
	DECLARE objname VARCHAR(2048) DEFAULT NULL;
BEGIN
	SELECT
		(COALESCE(RD.ref || ' / ', ' ') || RD.name || ' (' || RD.osm_id || ')') INTO objname
	FROM planet_osm_line RD,
		(SELECT
			nn_gid,
			nn_dist
		FROM	pgis_fn_nn(
			ST_Transform(ST_SetSRID(ST_MakePoint(coordX, coordY),4269),900913),
			15,
			10,
			10,
			'planet_osm_line',
			'true',	
			'osm_id',
			'way')
	ORDER BY nn_dist ASC LIMIT 1) RDS
	WHERE RD.osm_id = RDS.nn_gid;
	

	IF objname IS NULL THEN
		SELECT
			(COALESCE(RD.ref || ' / ', ' ') || RD.name) INTO objname
		FROM planet_osm_roads RD,
			(SELECT
				nn_gid,
				nn_dist
			FROM	pgis_fn_nn(
				ST_Transform(ST_SetSRID(ST_MakePoint(coordX, coordY),4269),900913),
				15,
				10,
				10,
				'planet_osm_roads',
				'true',	
				'osm_id',
				'way')
		ORDER BY nn_dist ASC LIMIT 1) RDS
		WHERE RD.osm_id = RDS.nn_gid;
	END IF;

	RETURN objname;
END;
$$ LANGUAGE plpgsql;
