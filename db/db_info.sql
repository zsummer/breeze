/*
Navicat MySQL Data Transfer

Source Server         : 10.0.7.21
Source Server Version : 50149
Source Host           : 10.0.7.21:3306
Source Database       : db_info

Target Server Type    : MYSQL
Target Server Version : 50149
File Encoding         : 65001

Date: 2014-11-05 19:37:46
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `tb_account`
-- ----------------------------
DROP TABLE IF EXISTS `tb_account`;
CREATE TABLE `tb_account` (
  `accID` bigint(20) unsigned NOT NULL,
  `accName` varchar(255) NOT NULL DEFAULT '',
  `diamond` int(10) unsigned NOT NULL DEFAULT '0',
  `giftDmd` int(10) unsigned NOT NULL DEFAULT '0',
  `hisDiamond` int(10) unsigned NOT NULL DEFAULT '0',
  `hisGiftDmd` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`accID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_account
-- ----------------------------
INSERT INTO tb_account VALUES ('1', 'zhangyawei', '0', '0', '0', '0');
INSERT INTO tb_account VALUES ('2', 'zhangyawei2', '0', '0', '0', '0');
INSERT INTO tb_account VALUES ('5', '', '0', '0', '0', '0');
INSERT INTO tb_account VALUES ('6', '', '0', '0', '0', '0');
INSERT INTO tb_account VALUES ('8', '', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `tb_character`
-- ----------------------------
DROP TABLE IF EXISTS `tb_character`;
CREATE TABLE `tb_character` (
  `charID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `accID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `charName` varchar(255) NOT NULL DEFAULT '',
  `iconID` int(10) unsigned NOT NULL DEFAULT '0',
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`charID`),
  UNIQUE KEY `accID` (`accID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tb_character
-- ----------------------------

-- ----------------------------
-- Procedure structure for `AutoSelectAccount`
-- ----------------------------
DROP PROCEDURE IF EXISTS `AutoSelectAccount`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `AutoSelectAccount`(IN `v_accID` bigint)
tag:BEGIN 
	declare v_accName varchar(20);
  declare v_diamond  int(10) unsigned;
  declare v_giftDmd int(10) unsigned;
  declare v_hisDiamond int(10) unsigned;
  declare v_hisGiftDmd int(10) unsigned;

	select a.accName, a.diamond, a.giftDmd, a.hisDiamond, a.hisGiftDmd 
		into v_accName, v_diamond,v_giftDmd,  v_hisDiamond,v_hisGiftDmd 
		from tb_account a where a.accID = v_accID;

  
	if( v_accName is NULL) THEN
		 select "", 0,0,0,0 into v_accName, v_diamond,v_giftDmd,  v_hisDiamond,v_hisGiftDmd ;
		 insert into tb_account(accID, accName, diamond, giftDmd, hisDiamond, hisGiftDmd) 
				values(v_accID, v_accName, v_diamond,v_giftDmd,  v_hisDiamond,v_hisGiftDmd );
	end if;
				
  select v_accName, v_diamond,v_giftDmd,  v_hisDiamond,v_hisGiftDmd,
				c.charID, c.charName, c.iconID, c.`level` from tb_character c where c.accID = v_accID;
				
END
;;
DELIMITER ;
