<div class="listItem">
	<span class="avatar"><span class="img"><img src="<%=contact.avatar?contact.avatar:'img/avatarEmpty.png'%>" /></span></span>
    <div class="data">
        <div class="detailsRow">
            <a class="userProfile" href="javascript:void(0);">
                <span class="name editableTxt"><%=contact.alias%></span>
                <span class="bitprofileIcon <%if(contact.bitprofile){%>on<%}%>"></span>
            </a>
            <a class="detail s_titled transactions" href="javascript:void(0);"><%=contact.transactions?contact.transactions:"0"%></a>
        </div>
        <div class="detailsRow">
            <div class="controls">
            	<a class="btn send" href="javascript:void(0);"></a>
            	<a class="btn remove" href="javascript:void(0);"></a>
            </div>
            <a class="address" href="javascript:void(0);"><%=contact.address%></a>
        </div>
    </div>
    <div class="controls removing">
        <div class="txt s_title">removing contact (<span class="time">5</span>)</div>
        <a class="btn btntxt cancel" href="javascript:void(0);"></a>
    </div>
</div>
