<?php
class Pages_Controller extends Template_Controller {

	public $template = 'pages/base'; //defaults to template but you can set your own view file

	public $auto_render = TRUE; //defaults to true, renders the template after the controller method is done

	public function __construct()
	{
		parent::__construct(); //necessary
	}

	public function index()
	{
		$this->template->title = 'Maemo5 application for car enthusiasts and speed freaks';
		$this->template->header = 'Home';
		$this->template->content = '
SpeedFreak is a free application for your mobile that allows you to measure your car\'s performance such as acceleration and top speed. In order to make it even 
more interesting you can compete against others on our leaderboards to see who\'s car packs the most punch!		
<br /><br />

SpeedFreak is developed by group of enthusiastic programmers with passion for speed and OpenSource. If you want to get involved by contributing code, ideas, bug reports, translation and more just click on
community link!
';
		$this->template->sidebar_title = 'SpeedFreak for Nokia N900';
		$this->template->sidebar_content ='
<img src="'.url::base().'static/img/speedfreak_n900.png" /><br />
<p>Download SpeedFreak for Nokia N900.</p>
<p><a href="#" class="link"><span><span>Download now</span></span></a></p>
';



	}

	public function leaderboards($category='')
	{
		//@todo: Fix this hack. OMG what a horrible hack. That's what I get for coding at 4am =)
		$categories = array('acceleration-0-20' => 'Acceleration from 0 to 20 km/h', 'acceleration-0-40' => 'Acceleration from 0 to 40 km/h', 'acceleration-0-100'=> 'Acceleration from 0 to 100 km/h');

		if (!array_key_exists($category,$categories))
		$category='acceleration-0-100';
			
		$this->template->title = $categories[$category];

		$results = new Result_Model();
		if ($rows=$results->get_results($category,10)){
			$output = '';
			foreach ($rows as $r){
				$output .= '
			<tr>
	<td align="right">'.$r->username.'</td>
	<td align="center">'.$r->value.' seconds</td>
	<td>'.$r->result_date.'</td>
</tr>';
			}
			$output ='
<table cellspacing="20" cellpadding="20">
<tr>
	<td><strong>Nick</strong></td>
	<td><strong>Record (seconds)</strong></td>
	<td><strong>Date</strong></td>
</tr>
'.$output.'
</table>
		
';
		}
		else
		$output="No results :(";



		$this->template->header = $categories[$category];
		$this->template->content = $output;
		$this->template->sidebar_title = 'Categories';
		$this->template->sidebar_content ='
<ul class="list">
	<li><a href="'.url::site('pages/leaderboards/acceleration-0-20').'" title="Leaderboard for acceleration from 0 to 20 km/h category">Acceleration from 0 to 20 km/h</a></li> 
	<li><a href="'.url::site('pages/leaderboards/acceleration-0-40').'" title="Leaderboard for acceleration from 0 to 40 km/h category">Acceleration from 0 to 40 km/h</a></li> 
	<li><a href="'.url::site('pages/leaderboards/acceleration-0-100').'" title="Leaderboard for acceleration from 0 to 100 km/h category">Acceleration from 0 to 100 km/h</a></li> 
</ul>
';



	}
	
	public function screenshots()
	{
		$this->template->title = 'Screenshots';
		$this->template->header = 'Screenshots';
		$this->template->content = '
Our freaky elfs are still working on those. Check back later =)
';
		$this->template->sidebar_title = 'SpeedFreak for Nokia N900';
		$this->template->sidebar_content ='
<img src="'.url::base().'static/img/speedfreak_n900.png" /><br />
<p>Download SpeedFreak for Nokia N900.</p>
<p><a href="#" class="link"><span><span>Download now</span></span></a></p>
';



	}
}