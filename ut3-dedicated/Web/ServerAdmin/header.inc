<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
	<title>UT3 WebAdmin - <%page.title%></title>
	<link rel="stylesheet" type="text/css" href="/images/ut3.css" title="Unreal Tournament 3" />
	<%webadminskins.meta%>
	<link rel="shortcut icon" href="/images/favicon.ico" type="image/x-icon" />
	<meta name="generator" content="UT3 WebAdmin v<%build.version%> - <%build.timestamp%>" />
	<script type="text/javascript" src="/images/jquery.js<%client.gzip%>"></script>
	<script type="text/javascript" src="/images/base.js<%client.gzip%>"></script>
	<%html.headers%>
</head>
<body>

<div id="header">
<h1><span>UT3 WebAdmin</span></h1>
<h3 id="pageUri"><%page.uri%></h3>
<h4 id="adminName">Welcome <span class="username"><%admin.name%></span></h4>
<h2 id="pageTitle"><%page.title%></h2>
<p id="pageDescription"><%page.description%></p>
</div>

<div id="messages">
<%messages%>
</div>
