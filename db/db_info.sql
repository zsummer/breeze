/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50150
Source Host           : 127.0.0.1:3306
Source Database       : db_info

Target Server Type    : MYSQL
Target Server Version : 50150
File Encoding         : 65001

Date: 2014-11-17 00:47:56
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
INSERT INTO tb_account VALUES ('3', 'zhangyawei0000', '0', '0', '0', '0');
INSERT INTO tb_account VALUES ('4', '', '0', '0', '0', '0');
INSERT INTO tb_account VALUES ('7', '', '0', '0', '0', '0');

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
  KEY `accID` (`accID`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tb_character
-- ----------------------------
INSERT INTO tb_character VALUES ('0', '3', 'fd', '0', '0');
INSERT INTO tb_character VALUES ('2', '3', 'ddd', '0', '0');
INSERT INTO tb_character VALUES ('3', '3', 'eeee', '0', '0');

-- ----------------------------
-- Procedure structure for `AutoSelectAccount`
-- ----------------------------
DROP PROCEDURE IF EXISTS `AutoSelectAccount`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `AutoSelectAccount`(IN `v_accID` bigint)
tag:BEGIN 
	declare v_accName varchar(20);

	select a.accName into v_accName from tb_account a where a.accID = v_accID;


	if( v_accName is NULL) THEN
		 insert into tb_account(accID, accName, diamond, giftDmd, hisDiamond, hisGiftDmd) values(v_accID, "", 0,0,0,0);
	end if;
				
	select a.accName, a.diamond, a.giftDmd, a.hisDiamond, a.hisGiftDmd, c.charID, c.charName, c.iconID, c.`level` 
		from tb_account a  left join tb_character c on a.accID = c.accID where a.accID = v_accID;
END
;;
DELIMITER ;
