CREATE TABLE IF NOT EXISTS `znote` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `version` varchar(30) NOT NULL COMMENT 'Znote AAC version',
  `installed` int(10) NOT NULL,
  `cached` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

INSERT INTO `znote` (`version`, `installed`) VALUES
('1.5_SVN', '1542829782');

CREATE TABLE IF NOT EXISTS `znote_accounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NOT NULL,
  `ip` int(10) UNSIGNED NOT NULL,
  `created` int(10) NOT NULL,
  `points` int(10) DEFAULT 0,
  `cooldown` int(10) DEFAULT 0,
  `active` tinyint(4) NOT NULL DEFAULT '0',
  `activekey` int(11) NOT NULL DEFAULT '0',
  `flag` varchar(20) NOT NULL,
  `secret` char(16) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

INSERT INTO `znote_accounts` (`account_id`, `ip`, `created`, `flag`) VALUES
('1', '0', '1542829782', '');

CREATE TABLE IF NOT EXISTS `znote_news` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(30) NOT NULL,
  `text` text NOT NULL,
  `date` int(11) NOT NULL,
  `pid` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_images` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(30) NOT NULL,
  `desc` text NOT NULL,
  `date` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `image` varchar(30) NOT NULL,
  `account_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_paypal` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `txn_id` varchar(30) NOT NULL,
  `email` varchar(255) NOT NULL,
  `accid` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `points` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_paygol` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `points` int(11) NOT NULL,
  `message_id` varchar(255) NOT NULL,
  `service_id` varchar(255) NOT NULL,
  `shortcode` varchar(255) NOT NULL,
  `keyword` varchar(255) NOT NULL,
  `message` varchar(255) NOT NULL,
  `sender` varchar(255) NOT NULL,
  `operator` varchar(255) NOT NULL,
  `country` varchar(255) NOT NULL,
  `currency` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `player_id` int(11) NOT NULL,
  `created` int(11) NOT NULL,
  `hide_char` tinyint(4) NOT NULL,
  `comment` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

INSERT INTO `znote_players` (`player_id`, `created`, `hide_char`, `comment`) VALUES
('1', '1542829782', '0', '');

CREATE TABLE IF NOT EXISTS `znote_player_reports` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `posx` int(6) NOT NULL,
  `posy` int(6) NOT NULL,
  `posz` int(6) NOT NULL,
  `report_description` VARCHAR(255) NOT NULL,
  `date` INT(11) NOT NULL,
  `status` TINYINT(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_changelog` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `text` VARCHAR(255) NOT NULL,
  `time` INT(11) NOT NULL,
  `report_id` INT(11) NOT NULL,
  `status` TINYINT(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_shop` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) NOT NULL,
  `itemid` int(11) DEFAULT NULL,
  `count` int(11) NOT NULL DEFAULT '1',
  `description` varchar(255) NOT NULL,
  `points` int(11) NOT NULL DEFAULT '10',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_shop_logs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NOT NULL,
  `player_id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `itemid` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `points` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_shop_orders` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `itemid` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_visitors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ip` int(11) NOT NULL,
  `value` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_visitors_details` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ip` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `type` tinyint(4) NOT NULL,
  `account_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_forum` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `access` tinyint(4) NOT NULL,
  `closed` tinyint(4) NOT NULL,
  `hidden` tinyint(4) NOT NULL,
  `guild_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

INSERT INTO `znote_forum` (`name`, `access`, `closed`, `hidden`, `guild_id`) VALUES
('Staff Board', '4', '0', '0', '0'),
('Tutors Board', '2', '0', '0', '0'),
('Discussion', '1', '0', '0', '0'),
('Feedback', '1', '0', '1', '0');

CREATE TABLE IF NOT EXISTS `znote_forum_threads` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `forum_id` int(11) NOT NULL,
  `player_id` int(11) NOT NULL,
  `player_name` varchar(50) NOT NULL,
  `title` varchar(50) NOT NULL,
  `text` text NOT NULL,
  `created` int(11) NOT NULL,
  `updated` int(11) NOT NULL,
  `sticky` tinyint(4) NOT NULL,
  `hidden` tinyint(4) NOT NULL,
  `closed` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_forum_posts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `thread_id` int(11) NOT NULL,
  `player_id` int(11) NOT NULL,
  `player_name` varchar(50) NOT NULL,
  `text` text NOT NULL,
  `created` int(11) NOT NULL,
  `updated` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_deleted_characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `original_account_id` int(11) NOT NULL,
  `character_name` varchar(255) NOT NULL,
  `time` datetime NOT NULL,
  `done` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_guild_wars` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `limit` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  FOREIGN KEY (`id`) REFERENCES `guild_wars` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_tickets` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `owner` int(11) NOT NULL,
  `username` varchar(32) CHARACTER SET latin1 NOT NULL,
  `subject` text CHARACTER SET latin1 NOT NULL,
  `message` text CHARACTER SET latin1 NOT NULL,
  `ip` int(11) NOT NULL,
  `creation` int(11) NOT NULL,
  `status` varchar(20) CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_tickets_replies` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tid` int(11) NOT NULL,
  `username` varchar(32) CHARACTER SET latin1 NOT NULL,
  `message` text CHARACTER SET latin1 NOT NULL,
  `created` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `znote_global_storage` (
  `key` VARCHAR(32) NOT NULL,
  `value` TEXT NOT NULL,
  UNIQUE (`key`)
) ENGINE=InnoDB;

