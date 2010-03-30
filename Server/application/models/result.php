<?php defined('SYSPATH') or die('No direct script access.');
/*
 * Results model for creating and manipulating results
 *
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

class Result_Model extends Model {

    public function __construct(){

        // load database library into $this->db
        parent::__construct();
    }

    /*
     * Fetch results
     *
     * @param string $category From which category should we get results
     * @param integer $limit How many results to return
     * @return object|bool Returns object containing results if everything is ok and false otherwise
     */
    public function get_results($category, $limit=10){
        $results = $this->db->query("SELECT u.username as username, c.unit as unit, r.value as value, r.result_date as result_date, c.slug as slug FROM users u, results r, categories c WHERE r.user_id=u.id AND c.slug = ? AND r.cat_id=c.id ORDER BY r.value ASC LIMIT ".(int)$limit, $category);
    if ($results->count()>0)
            return $results;
        else
            return false;
    }

    /*
     * Insert new result
     *
     * @param string $category Category name (slug)
     * @return bool True if exists and False otherwise
     */
    public function insert($category, $username, $value){
	$cat = New Category_Model();
	$category = $cat->get_id($category);
	$user = New User_Model();
	$username = $user->get_id($username);
        $results = $this->db->query("INSERT INTO results SET cat_id = ?, user_id = ?, value = ?, result_date = NOW()", $category, $username, $value);
        if ($results)
            return true;
        else
            return false;
    }

}