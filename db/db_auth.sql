/*
Navicat MySQL Data Transfer

Source Server         : 10.0.7.21
Source Server Version : 50149
Source Host           : 10.0.7.21:3306
Source Database       : db_auth

Target Server Type    : MYSQL
Target Server Version : 50149
File Encoding         : 65001

Date: 2014-11-05 19:37:38
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `tb_auth`
-- ----------------------------
DROP TABLE IF EXISTS `tb_auth`;
CREATE TABLE `tb_auth` (
  `account` varchar(20) NOT NULL DEFAULT '',
  `pwd` varchar(20) NOT NULL DEFAULT '',
  `accID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`account`),
  UNIQUE KEY `accID` (`accID`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_auth
-- ----------------------------
INSERT INTO tb_auth VALUES ('test0001', '123', '1');
INSERT INTO tb_auth VALUES ('test0002', '123', '2');
