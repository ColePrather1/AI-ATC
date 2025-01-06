
--CREATE TABLE 


--CREATE TABLE constants();

CREATE TABLE atc_system(
    timestamp INTEGER PRIMARY KEY,
    ctlr_paired BOOlEAN,
        -- T/F
    rf_rx_active BOOlEAN,
        -- T/F
    rf_tx_active BOOlEAN
        -- T/F
);


-- Less frequent (non-consistent frequency) updates compared to flight_status
-- i.e. TX>Plane, Constraints, User-Driven Actions
CREATE TABLE system_status (
    timestamp INTEGER PRIMARY KEY,
    control_mode INTEGER,
        -- 0 = AUTO
        -- 1 = ASSIST
        -- 2 = MANUAL
        -- 3 = EMERGENCY
        -- 4 = PAIRING
    paired BOOlEAN,
        -- T/F
    throttle_lock BOOlEAN,
        -- T/F
    holding_pattern BOOlEAN,
        -- T/F
    taxi_only BOOlEAN,
        -- T/F
    gps_active BOOlEAN
        -- T/F
        -- Only exception to Tx/Rx "rule", hopefully not frequent


);

-- More frequent (semi-fixed frequency) updates compared to system_status
-- i.e. RX<Plane, Real-time info, Event-Driven Actions
CREATE TABLE flight_status (
    timestamp INTEGER PRIMARY KEY,

    battery_level REAL,
        -- %
    signal_strength REAL,
        -- RSSI dB
    flying BOOlEAN
        -- T/F


);

CREATE TABLE flight_vars (
    timestamp INTEGER PRIMARY KEY,
    pitch REAL,
    roll REAL,
    yaw REAL,
    distance REAL

);

CREATE TABLE servos (
    timestamp INTEGER PRIMARY KEY,
    throttle INTEGER,
    elevator INTEGER,
    rudder INTEGER,
    left_aileron INTEGER,
    right_aileron INTEGER
);

CREATE TABLE gps_data (
    timestamp INTEGER PRIMARY KEY,
    latitude REAL,
    longitude REAL,
    altitude REAL,
    speed REAL,
    satellites INTEGER,
    signal_strength INTEGER
);

CREATE TABLE imu_data (
    timestamp INTEGER PRIMARY KEY,
    accel_x REAL,
    accel_y REAL,
    accel_z REAL,
    gyro_x REAL,
    gyro_y REAL,
    gyro_z REAL,
    mag_x REAL,
    mag_y REAL,
    mag_z REAL
);

CREATE TABLE baro_data (
    timestamp INTEGER PRIMARY KEY,
    pressure REAL,
    temperature REAL,
    calculated_altitude REAL
);



CREATE TABLE pid_data (
    timestamp INTEGER PRIMARY KEY,
-- Ailerons / Stabilize
    roll_p REAL,
    roll_i REAL,
    roll_d REAL,
-- Rudder / Heading
    yaw_p REAL,
    yaw_i REAL,
    yaw_d REAL,
-- Elevator (desired angle)
    pitch_p REAL,
    pitch_i REAL,
    pitch_d REAL
-- Elevator (desired altitude)
--    alt_p REAL,
--    alt_i REAL,
--    alt_d REAL
);



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------








