<?php if (empty($head))$head=''; echo View::factory('pages/head')->set('title',$title)->set('head',$head)->render(); ?>
<body id="default">
	<div class="top-bg"> 
	<div id="main"> 
		<div id="header"> 
			<div class="menu"> 
				<div class="left-bg"> 
					<div class="right-bg"> 
						<a href="<?php echo url::base(); ?>" title="Return back to SpeedFreak's homepage" class="home-link"><img src="<?php echo url::base(); ?>static/img/home-link.gif" alt="SpeedFreak home icon" /></a> 
						<ul> 
							<li><a href="<?php echo url::site('pages/index'); ?>" title="Return back to SpeedFreak's homepage">Home</a></li> 
							<li><a href="<?php echo url::site('pages/screenshots'); ?>" title="See SpeedFreak in action">Screenshots</a></li>
							<li><a href="<?php echo url::site('pages/leaderboards'); ?>" title="See who's crusing and who's losing">Leaderboards</a></li>
							<li><a href="http://garage.maemo.org/projects/speedfreak/" title="Get involved in developing SpeedFreak">Community</a></li>
							<li><a href="https://garage.maemo.org/project/memberlist.php?group_id=1395" title="See the team behind SpeedFreak">Credits</a></li>
						</ul> 
					</div> 
				</div> 
			</div> 
			<div class="logo"><a href="<?php echo url::base(); ?>" title="Return back to SpeedFreak's homepage"><img src="<?php echo url::base(); ?>static/img/logo.jpg" alt="SpeedFreak logo" /></a></div> 
		</div> 
			<div class="box1"> 
				<div class="left-border"> 
					<div class="right-border"> 
						<div class="top-border"> 
							<div class="left-bot"> 
								<div class="right-bot"> 
									<div class="left-top"> 
										<div class="right-top"> 
											<div class="indent4 line2"> 
												<div class="container"> 
													<div class="col-1"> 
														<h1><?php echo $header; ?></h1> 
														<?php echo $content; ?> 
													</div> 
													<div class="col-2 space1"> 
														<h2><?php echo $sidebar_title; ?></h2> 
														<?php echo $sidebar_content; ?>  
													</div> 
												</div> 
											</div> 
										</div> 
									</div> 
								</div> 
							</div> 
						</div> 
					</div> 
				</div> 
			</div>
<?php echo View::factory('pages/footer')->render(); ?>