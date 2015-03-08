/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50150
Source Host           : 127.0.0.1:3306
Source Database       : db_info

Target Server Type    : MYSQL
Target Server Version : 50150
File Encoding         : 65001

Date: 2015-03-09 00:27:21
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `tb_user`
-- ----------------------------
DROP TABLE IF EXISTS `tb_user`;
CREATE TABLE `tb_user` (
  `uid` bigint(20) unsigned NOT NULL,
  `nickname` varchar(255) NOT NULL DEFAULT '',
  `iconID` int(10) NOT NULL DEFAULT '0',
  `level` int(10) NOT NULL DEFAULT '0',
  `diamond` int(10) NOT NULL DEFAULT '0',
  `giftDiamond` int(10) NOT NULL DEFAULT '0',
  `historyDiamond` int(10) NOT NULL DEFAULT '0',
  `bag` blob,
  `joinTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`uid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_user
-- ----------------------------

-- ----------------------------
-- Procedure structure for `CreateUser`
-- ----------------------------
DROP PROCEDURE IF EXISTS `CreateUser`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `CreateUser`(IN `v_uid` bigint,IN `v_nickname` varchar(20),IN `v_iconID` int)
tag:BEGIN 
	declare v_temp varchar(20);

	select nickname into v_temp from tb_user where uid = v_uid or nickname = v_nickname;


	if( v_temp is NULL) THEN
		 insert into tb_user(uid, nickname, iconID, joinTime) values(v_uid, v_nickname, v_iconID, now());
	end if;

	select uid, nickname, iconID, `level`, diamond, giftDiamond,historyDiamond, UNIX_TIMESTAMP(joinTime) from tb_user where uid = v_uid;
END
;;
DELIMITER ;
