<?php
/**
 * Static pages controller
 * 
 * @todo Refactoring needed
 * @author Artem Daniliants <artem@daniliants.com>
 *
 */
class Pages_Controller extends Template_Controller {

	public $template = 'pages/base'; //defaults to template but you can set your own view file

	public $auto_render = TRUE; //defaults to true, renders the template after the controller method is done

	public function __construct()
	{
		parent::__construct(); //necessary
	}
	
	
	/**
	 * Generate lightbox markup
	 * 
	 * @param array $images
	 */
	private function lightbox($images){
		$output = '';
		foreach ($images as $i){
			$output .= '<a href="'.url::base().'static/img/screenshots/big/'.$i['img'].'.png" rel="lightbox[screenshots]" title="'.$i['title'].'"><img border=0 class="lightbox_thumbs" src="'.url::base().'static/img/screenshots/small/'.$i['img'].'.png" alt="'.$i['alt'].'"/></a>';
		}
		return $output;
	}

	public function index()
	{

		$this->template->title = 'Maemo5 application for car enthusiasts and speed freaks';
		$this->template->header = 'Home';
		
		$this->template->content = '
<center>
<object width="480" height="385"><param name="movie" value="http://www.youtube.com/v/edKtuF__L_8&hl=en_US&fs=1&rel=0&color1=0x3a3a3a&color2=0x999999"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/edKtuF__L_8&hl=en_US&fs=1&rel=0&color1=0x3a3a3a&color2=0x999999" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="480" height="385"></embed></object>
</center>
<br />
<br />		
			
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
<p><a href="https://garage.maemo.org/projects/speedfreak/" class="link"><span><span>Download now</span></span></a></p>
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
		$this->template->head = '
		<script type="text/javascript" src="'.url::base().'static/js/prototype.js"></script>
		<script type="text/javascript" src="'.url::base().'static/js/scriptaculous.js?load=effects,builder"></script>
		<script type="text/javascript" src="'.url::base().'static/js/lightbox.js"></script>
		<link rel="stylesheet" href="'.url::base().'static/css/lightbox.css" type="text/css" media="screen" />
		';
		
		$screenshots=array();
		$screenshots[0]['img']=1;
		$screenshots[0]['alt']='Main window';
		$screenshots[0]['title']='OpenSource Maemo 5 application for car enthusiasts';
		
		$screenshots[1]['img']=2;
		$screenshots[1]['alt']='Acceleration screen';
		$screenshots[1]['title']='See how fast your car accelerates and compete for the first position on our leaderboards';
		
		$screenshots[2]['img']=3;
		$screenshots[2]['alt']='Categories window';
		$screenshots[2]['title']='You can compete in defferent categories';
		
		$screenshots[3]['img']=4;
		$screenshots[3]['alt']='Route window';
		$screenshots[3]['title']='Save your roadtrip route';
		
		$screenshots[4]['img']=5;
		$screenshots[4]['alt']='Registration window';
		$screenshots[4]['title']="Participating in our community is as easy as registering for an account";
		
		$screenshots[5]['img']=6;
		$screenshots[5]['alt']='Credits window';
		$screenshots[5]['title']='SpeedFreak is developed by a group of dedicated contributors. Join us and help make it even better!';
		
		$lightbox = $this->lightbox($screenshots);
		
		$this->template->content = '
'.$lightbox.'
';
		$this->template->sidebar_title = 'SpeedFreak for Nokia N900';
		$this->template->sidebar_content ='
<img src="'.url::base().'static/img/speedfreak_n900.png" /><br />
<p>Download SpeedFreak for Nokia N900.</p>
<p><a href="#" class="link"><span><span>Download now</span></span></a></p>
';

	}
}