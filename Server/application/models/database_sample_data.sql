-- MySQL dump 10.11
--
-- Host: localhost    Database: speedfreak
-- ------------------------------------------------------
-- Server version	5.0.51a-24+lenny3-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Dumping data for table `categories`
--

LOCK TABLES `categories` WRITE;
/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` VALUES (1,'acceleration-0-20','Acceleration from 0km/h to 20km/h','km/h'),(2,'acceleration-0-40','Acceleration from 0km/h to 40km/h','km/h'),(3,'acceleration-0-100','Acceleration from 0km/h to 100km/h','km/h');
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `results`
--

LOCK TABLES `results` WRITE;
/*!40000 ALTER TABLE `results` DISABLE KEYS */;
INSERT INTO `results` VALUES (3,4,2,'2010-04-01 04:55:39'),(3,5,3,'2010-04-01 04:55:46'),(3,6,5,'2010-04-01 04:55:55'),(3,7,12,'2010-04-01 04:56:01'),(3,8,19,'2010-04-01 04:56:07'),(3,9,21,'2010-04-01 04:56:14'),(3,10,24,'2010-04-01 04:56:21'),(3,11,30,'2010-04-01 04:56:29'),(3,12,33,'2010-04-01 04:56:33'),(3,12,35,'2010-04-01 04:56:36'),(3,13,35,'2010-04-01 04:56:40'),(3,14,46,'2010-04-01 04:56:47');
/*!40000 ALTER TABLE `results` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (4,'Seppo','dfs','seppo@seppo.com'),(5,'Artem','dfs','seppzo@seppo.com'),(6,'Jukka','dfs','seppzzo@seppo.com'),(7,'Kai','dfs','seppzzzo@seppo.com'),(8,'Obama','dfs','seppzzszo@seppo.com'),(9,'Halonen','dfs','seppzszszo@seppo.com'),(10,'Pertti','dfs','seppzszzszo@seppo.com'),(11,'Temchu','dfs','seppzszzszo@sezppo.com'),(12,'Random','dfs','seppzszzszo@zsezppo.com'),(13,'Martin','dfs','szeppzszzszo@zsezppo.com'),(14,'Johnny','dfs','szeppzszzszo@zsezppzo.com');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-04-01  2:22:27
