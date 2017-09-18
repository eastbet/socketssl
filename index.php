<?
	//шаблон хранилища auth
?>

<div id="unlogged" class="unlogged">
<div style="float:left;">
  <input type="text" value="логин" deftitle="логин" id="login" class="textbox" onfocusin="loginin();" onfocusout="loginout();" onKeyPress="loginpres(event);"/>
  <input type="text" value="пароль" deftitle="пароль" id="password" class="textbox" onfocusin="passwordin()" onfocusout="passwordout()" onKeyPress="loginpres(event);"/>
  <input type="button" value="Вход" class="enter" onclick="loginclick();"/>
   </div><div style="float:left;margin-top:2px;">         
    <input type="checkbox"  value="checkbox" id="CHECKLOGIN" checked="checked" style="margin-left:3px;opacity:0.6;float:left;margin-top:2px;" onclick="ckl1();"/>
    <span isflash="1" style="font-size:11px;margin-left:2px; color:#CFCFCF;">Запомнить</span>
    <a href="/auth/remember1/" isflash="1" style="font-size:11px;margin-left:10px;color:#CFCFCF;">Забыли пароль?</a>
    
    <a isflash="1" class="reg" href="/auth/registration/">Открыть счет</a></div>
    
</div>

<div id="logged" class="logged" style="display:none;"><span id="uid_name" style="color:#CFCFCF;font-weight:bold;padding-right:5px;"></span><span id="uid_log" style="color:#FFFFFF;font-weight:bold;"></span><span id="uid_onplay" style="color:#CFCFCF;font-weight:bold;padding-right:5px;">В игре:</span><span style="color:#FFFFFF;font-weight:bold; "> ______</span><span id="uid_balance" style="color:#CFCFCF;font-weight:bold;padding-right:5px;">Мой баланс:</span><span style="color:#FFFFFF;font-weight:bold;"> ______</span><span  style="color:#CFCFCF;font-weight:bold;padding-right:5px;cursor:pointer;" onclick="showWarning(war208,'OK','',0,null);"></span><span style="color:#FFFFFF;font-weight:bold;cursor:pointer;" onclick="showWarning(war208,'OK','',0,null);"></span><div id="setbonus" style="float:left;display:none;cursor:pointer;text-decoration:underline;color:#CFCFCF;margin-top:-1px;font-size:12px;margin-right:15px;"></div><div id="ath" style="width:250px;float:left;margin-top:-2px;"><a href="/auth/istoria/"><div id="lk">Личный кабинет</div></a><a href="/auth/payment/"><div id="ppk">Пополнить</div></a>
    </div>

    <div style="text-decoration:underline;color:#CFCFCF;font-size:11px;float:right;margin-right:60px;font-weight:bold;cursor:pointer;" onclick="loginexit();">
        Выход
    </div>
    
</div>



