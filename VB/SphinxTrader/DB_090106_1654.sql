# SQL Manager 2005 for MySQL 3.6.5.1
# ---------------------------------------
# Host     : localhost
# Port     : 3306
# Database : broker


SET FOREIGN_KEY_CHECKS=0;

DROP DATABASE IF EXISTS `broker`;

CREATE DATABASE `broker`
    CHARACTER SET 'latin1'
    COLLATE 'latin1_swedish_ci';

USE `broker`;

#
# Structure for the `accs` table : 
#

DROP TABLE IF EXISTS `accs`;

CREATE TABLE `accs` (
  `ID` int(11) NOT NULL auto_increment,
  `Login` varchar(20) NOT NULL,
  `Pwd` varchar(20) NOT NULL,
  `Name` varchar(50) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Data for the `accs` table  (LIMIT 0,500)
#

INSERT INTO `accs` (`ID`, `Login`, `Pwd`, `Name`) VALUES 
  (1,'Login01','Pwd01','Name01'),
  (2,'Login02','Pwd02','Name02');

COMMIT;

#
# Structure for the `countrs` table : 
#

DROP TABLE IF EXISTS `countrs`;

CREATE TABLE `countrs` (
  `Country` char(20) NOT NULL,
  PRIMARY KEY  (`Country`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Structure for the `tools` table : 
#

DROP TABLE IF EXISTS `tools`;

CREATE TABLE `tools` (
  `ID` smallint(6) NOT NULL,
  `Tool` char(6) NOT NULL,
  `FractMult` mediumint(9) default NULL,
  `Spread` decimal(6,4) default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Data for the `tools` table  (LIMIT 0,500)
#

INSERT INTO `tools` (`ID`, `Tool`, `FractMult`, `Spread`) VALUES 
  (1,'EURUSD',10000,0.0002),
  (2,'GBPUSD',10000,0.0003),
  (3,'USDCHF',10000,0.0004),
  (4,'USDJPY',100,0.03),
  (5,'EURCHF',10000,0.0003),
  (6,'GOLD',10,1),
  (7,'_DJI',10,0);

COMMIT;

#
# Structure for the `types` table : 
#

DROP TABLE IF EXISTS `types`;

CREATE TABLE `types` (
  `ID` tinyint(4) NOT NULL,
  `Type` char(10) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Data for the `types` table  (LIMIT 0,500)
#

INSERT INTO `types` (`ID`, `Type`) VALUES 
  (1,'Buy'),
  (2,'Sell'),
  (3,'Buy stop'),
  (4,'Sell stop'),
  (5,'Buy limit'),
  (6,'Sell limit');

COMMIT;

#
# Structure for the `trades` table : 
#

DROP TABLE IF EXISTS `trades`;

CREATE TABLE `trades` (
  `ID` int(11) NOT NULL auto_increment,
  `IDAcc` int(11) default NULL,
  `TimeOpn` datetime NOT NULL,
  `IDType` tinyint(4) default NULL,
  `Vol` decimal(10,2) unsigned NOT NULL,
  `IDTool` smallint(6) default NULL,
  `PriceOpn` decimal(10,4) default NULL,
  `SL` decimal(10,4) default NULL,
  `TP` decimal(10,4) default NULL,
  `TimeCls` datetime default NULL,
  `PriceCls` decimal(9,4) default NULL,
  `Swap` decimal(6,2) unsigned default NULL,
  PRIMARY KEY  (`ID`),
  KEY `IDType` (`IDType`),
  KEY `IDAcc` (`IDAcc`),
  KEY `IDTool_2` (`IDTool`),
  CONSTRAINT `trades_fk` FOREIGN KEY (`IDType`) REFERENCES `types` (`ID`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `trades_fk1` FOREIGN KEY (`IDTool`) REFERENCES `tools` (`ID`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `trades_fk2` FOREIGN KEY (`IDAcc`) REFERENCES `accs` (`ID`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

#
# Data for the `trades` table  (LIMIT 0,500)
#

INSERT INTO `trades` (`ID`, `IDAcc`, `TimeOpn`, `IDType`, `Vol`, `IDTool`, `PriceOpn`, `SL`, `TP`, `TimeCls`, `PriceCls`, `Swap`) VALUES 
  (257,2,'2008-10-17 13:07:00',1,0.01,1,1.3408,1.3,1.4,'2008-10-17',1.4,NULL),
  (258,2,'2008-10-17 13:07:00',1,0.01,1,1.3408,1.3,1.4,'2008-10-17',1.4,NULL),
  (259,2,'2008-10-24 12:18:00',2,0.01,1,1.2578,1.3,1.4,'2008-10-24 12:18:00',1.4,NULL),
  (260,2,'2008-10-24 12:18:00',1,0.01,1,1.258,1.3,1.4,'2008-10-24 12:18:00',1.3,NULL),
  (261,2,'2008-10-24 12:18:00',2,0.01,3,1.1578,1.3,1.4,NULL,NULL,NULL),
  (262,2,'2008-10-24 12:18:00',1,0.01,3,1.1582,1.3,1.4,NULL,NULL,NULL);

COMMIT;

#
# Definition for the `Ins_Trades` procedure : 
#

DROP PROCEDURE IF EXISTS `Ins_Trades`;

CREATE PROCEDURE `Ins_Trades`(IN intIDAcc INTEGER(11), IN dtmTimeOpn DATETIME, IN tynIDType TINYINT, IN intVol INTEGER, IN smiIDTool SMALLINT, IN mdmFractMult MEDIUMINT, IN mdmPriceOpn MEDIUMINT, IN mdmSL MEDIUMINT, IN mdmTP MEDIUMINT)
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT ''
BEGIN
INSERT INTO trades 
    SET IDAcc = intIDAcc, TimeOpn = dtmTimeOpn, IDType = tynIDType,
        Vol = intVol / 100, IDTool = smiIDTool, PriceOpn = mdmPriceOpn / mdmFractMult,
        SL = mdmSL / mdmFractMult, TP = mdmTP / mdmFractMult;
END;

#
# Definition for the `Sel_Accs_ID` procedure : 
#

DROP PROCEDURE IF EXISTS `Sel_Accs_ID`;

CREATE PROCEDURE `Sel_Accs_ID`(IN chrLogin VARCHAR(20), IN chrPwd VARCHAR(20))
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT ''
BEGIN
     SELECT ID FROM `accs` WHERE (Login = chrLogin) AND (Pwd = chrPwd);
END;

#
# Definition for the `Sel_Test` procedure : 
#

DROP PROCEDURE IF EXISTS `Sel_Test`;

CREATE PROCEDURE `Sel_Test`(IN smiIDTool SMALLINT, IN mdmBid MEDIUMINT, IN mdmFractMult MEDIUMINT)
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT 'Convert pending orders into buy open orders.'
BEGIN
     select * from `trades`
            WHERE (`trades`.`SL` <= (mdmBid / mdmFractMult));
END;

#
# Definition for the `Sel_TradesHist` procedure : 
#

DROP PROCEDURE IF EXISTS `Sel_TradesHist`;

CREATE PROCEDURE `Sel_TradesHist`(IN intIDAcc INTEGER(11))
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT ''
BEGIN
     SELECT trades.ID, `trades`.`TimeOpn`, `trades`.`IDType`, types.Type, `trades`.`Vol`,
          `trades`.`IDTool`, tools.Tool, `trades`.`PriceOpn`, `trades`.`SL`, `trades`.`TP`,
          `trades`.`TimeCls`, `trades`.`PriceCls`, `trades`.`Swap`,
          `trades`.`PriceOpn` - `trades`.`PriceCls` AS `Profit`
          FROM types INNER JOIN
                 (tools INNER JOIN trades ON tools.ID = trades.IDTool)
                 ON types.ID = trades.IDType
            WHERE (`trades`.`IDAcc` = intIDAcc) AND
                  (isnull(`trades`.`PriceCls`) = FALSE);
END;

#
# Definition for the `Sel_TradesOpn` procedure : 
#

DROP PROCEDURE IF EXISTS `Sel_TradesOpn`;

CREATE PROCEDURE `Sel_TradesOpn`(IN intIDAcc INTEGER(11))
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT ''
BEGIN
     SELECT trades.ID, `trades`.`TimeOpn`, `trades`.`IDType`, types.Type,
            `trades`.`Vol`, `trades`.`IDTool`, tools.Tool, `trades`.`PriceOpn`,
            `trades`.`SL`, `trades`.`TP`, `trades`.`Swap`
            FROM types INNER JOIN
                 (tools INNER JOIN trades ON tools.ID = trades.IDTool)
                 ON types.ID = trades.IDType
            WHERE (`trades`.`IDAcc` = intIDAcc) AND
                  (isnull(`trades`.`PriceCls`)) AND
                  ((`trades`.`IDType` = 1) OR
                  (`trades`.`IDType` = 2));
END;

#
# Definition for the `Sel_TradesPend` procedure : 
#

DROP PROCEDURE IF EXISTS `Sel_TradesPend`;

CREATE PROCEDURE `Sel_TradesPend`(IN intIDAcc INTEGER(11))
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT ''
BEGIN
     SELECT trades.ID, `trades`.`TimeOpn`, `trades`.`IDType`, types.Type, `trades`.`Vol`,
            `trades`.`IDTool`, tools.Tool, `trades`.`PriceOpn`, `trades`.`SL`, `trades`.`TP`
            FROM types INNER JOIN
                 (tools INNER JOIN trades ON tools.ID = trades.IDTool)
                 ON types.ID = trades.IDType
            WHERE (`trades`.`IDAcc` = intIDAcc) AND
                  (isnull(`trades`.`PriceCls`)) AND
                  ((`trades`.`IDType` = 3) OR
                  (`trades`.`IDType` = 4) OR
                  (`trades`.`IDType` = 5) OR
                  (`trades`.`IDType` = 6));
END;

#
# Definition for the `Upd_Test` procedure : 
#

DROP PROCEDURE IF EXISTS `Upd_Test`;

CREATE PROCEDURE `Upd_Test`(IN dtmTimeTick DATETIME, IN smiIDTool SMALLINT, IN mdmBid MEDIUMINT, IN mdmAsk MEDIUMINT, IN mdmFractMult MEDIUMINT)
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT 'Convert pending orders into buy open orders.'
BEGIN
#Closing Buy positions at TP.
    UPDATE `trades`
        SET `trades`.`TimeCls` = dtmTimeTick,
            `trades`.`PriceCls` = `trades`.`TP`
                WHERE ((isnull(`trades`.`PriceCls`)) #Select open positions.
                      and (isnull(`trades`.`TP`) = FALSE) #Select the positions with TP set.
                      and (`trades`.`IDType` = 1)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`SL` >= (mdmBid / mdmFractMult)));
END;

#
# Definition for the `Upd_Trades` procedure : 
#

DROP PROCEDURE IF EXISTS `Upd_Trades`;

CREATE PROCEDURE `Upd_Trades`(IN dtmTimeTick DATETIME, IN smiIDTool SMALLINT, IN mdmBid MEDIUMINT, IN mdmAsk MEDIUMINT, IN mdmFractMult MEDIUMINT)
    NOT DETERMINISTIC
    SQL SECURITY DEFINER
    COMMENT 'Convert pending orders into buy open orders.'
BEGIN
#Opening at Buy Stops.
     UPDATE `trades`
            SET `trades`.`TimeOpn` = dtmTimeTick,
                IDType = 1
                WHERE ((`trades`.`IDType` = 3)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`PriceOpn` <= (mdmAsk / mdmFractMult)));
#Opening at Sell Stops.
     UPDATE `trades`
            SET `trades`.`TimeOpn` = dtmTimeTick,
                IDType = 2
                WHERE ((`trades`.`IDType` = 4)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`PriceOpn` >= (mdmBid / mdmFractMult)));
#Opening at Buy Limits.
     UPDATE `trades`
            SET `trades`.`TimeOpn` = dtmTimeTick,
                IDType = 1
                WHERE ((`trades`.`IDType` = 5)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`PriceOpn` >= (mdmAsk / mdmFractMult)));
#Opening at Sell Limits.
     UPDATE `trades`
            SET `trades`.`TimeOpn` = dtmTimeTick,
                IDType = 2
                WHERE ((`trades`.`IDType` = 6)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`PriceOpn` <= (mdmBid / mdmFractMult)));
#Closing Buy positions at SL.
    UPDATE `trades`
        SET `trades`.`TimeCls` = dtmTimeTick,
            `trades`.`PriceCls` = `trades`.`SL`
                WHERE ((isnull(`trades`.`PriceCls`)) #Select open positions.
                      and (isnull(`trades`.`SL`) = FALSE) #Select the positions with SL set.
                      and (`trades`.`IDType` = 1)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`SL` >= (mdmBid / mdmFractMult)));
#Closing Sell positions at SL.
    UPDATE `trades`
        SET `trades`.`TimeCls` = dtmTimeTick,
            `trades`.`PriceCls` = `trades`.`SL`
                WHERE ((isnull(`trades`.`PriceCls`)) #Select open positions.
                      and (isnull(`trades`.`SL`) = FALSE) #Select the positions with SL set.
                      and (`trades`.`IDType` = 2)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`SL` <= (mdmAsk / mdmFractMult)));
#Closing Buy positions at TP.
    UPDATE `trades` 
        SET `trades`.`TimeCls` = dtmTimeTick,
            `trades`.`PriceCls` = `trades`.`TP`
                WHERE ((isnull(`trades`.`PriceCls`)) #Select open positions.
                      and (isnull(`trades`.`TP`) = FALSE) #Select the positions with TP set.
                      and (`trades`.`IDType` = 1)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`TP` <= (mdmBid / mdmFractMult)));
#Closing Sell positions at TP.
    UPDATE `trades` 
        SET `trades`.`TimeCls` = dtmTimeTick,
            `trades`.`PriceCls` = `trades`.`TP`
                WHERE ((isnull(`trades`.`PriceCls`)) #Select open positions.
                      and (isnull(`trades`.`TP`) = FALSE) #Select the positions with TP set.
                      and (`trades`.`IDType` = 2)
                      and (`trades`.`IDTool` = smiIDTool)
                      and (`trades`.`TP` >= (mdmAsk / mdmFractMult)));
END;

#
# Definition for the `sel_trades_ord` view : 
#

DROP VIEW IF EXISTS `sel_trades_ord`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `sel_trades_ord` AS 
  select 
    `trades`.`IDTool` AS `IDTool`,
    `trades`.`IDType` AS `IDType`,
    `trades`.`PriceOpn` AS `PriceOpn`,
    `trades`.`TimeOpn` AS `TimeOpn` 
  from 
    `trades` 
  where 
    ((`trades`.`IDTool` = 4) and ((`trades`.`IDType` = 3) 
  or 
    (`trades`.`IDType` = 4) 
  or 
    (`trades`.`IDType` = 5) 
  or 
    (`trades`.`IDType` = 6)));

#
# Definition for the `sel_trades_work` view : 
#

DROP VIEW IF EXISTS `sel_trades_work`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `sel_trades_work` AS 
  select 
    `trades`.`ID` AS `ID`,
    `trades`.`IDType` AS `IDType`,
    `trades`.`IDTool` AS `IDTool`,
    `trades`.`PriceOpn` AS `PriceOpn`,
    `trades`.`SL` AS `SL`,
    `trades`.`PriceCls` AS `PriceCls` 
  from 
    `trades` 
  where 
    ((`trades`.`IDTool` = 4) and (`trades`.`IDType` = 1) and isnull(`trades`.`PriceCls`));

