/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50150
Source Host           : 127.0.0.1:3306
Source Database       : db_auth

Target Server Type    : MYSQL
Target Server Version : 50150
File Encoding         : 65001

Date: 2014-12-21 23:45:40
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `tb_auth`
-- ----------------------------
DROP TABLE IF EXISTS `tb_auth`;
CREATE TABLE `tb_auth` (
  `user` varchar(20) NOT NULL DEFAULT '',
  `passwd` varchar(20) NOT NULL DEFAULT '',
  `uid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`user`),
  UNIQUE KEY `accID` (`uid`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_auth
-- ----------------------------
INSERT INTO tb_auth VALUES ('test0001', '123', '1');
INSERT INTO tb_auth VALUES ('test0002', '123', '2');
INSERT INTO tb_auth VALUES ('zhangyawei0000', '123', '3');
INSERT INTO tb_auth VALUES ('zhangyawei0001', '123', '4');
INSERT INTO tb_auth VALUES ('zhangyawei0002', '123', '5');
INSERT INTO tb_auth VALUES ('zhangyawei0003', '123', '6');
INSERT INTO tb_auth VALUES ('zhangyawei0004', '123', '7');
INSERT INTO tb_auth VALUES ('zhangyawei0005', '123', '8');
