<%if(transaction.type=="mined"){%>
<div class="listItem mined" style="display: block;">
    <div class="header icon">
        <span class="detail s_titled userAddress"><%transaction.to%></span>
    </div>
    <div class="data">
        <div class="detailsRow">
            <span class="detail s_titled hash" title="<%=transaction.hash%>"><%=shortify(transaction.hash, 80)%></span>
            <span class="detail txtBalance">
                <span class="int"><%=transaction.amount.int%></span><span class="dec"><%=transaction.amount.dec%></span>
            </span>
        </div>
        <div class="detailsRow">
            <span class="detail time" title="<%=transaction.time%>"><%=$.timeago(transaction.time)%></span>
        </div>
    </div>
</div>
<%}else{%>
<div class="listItem <%=transaction.type%>" <%if(transaction.alias){%>contact="true"<%}%> style="display: block;">
    <div class="header icon">
        <span class="detail s_titled userAddress"><%=(transaction.type=="received")?transaction.to:transaction.from%></span>
    </div>
    <span class="avatar">
        <span class="img"><img src="<%=(transaction.alias && transaction.alias.avatar)?transaction.alias.avatar:'img/avatarEmpty.png'%>" onerror="errorAvatar($(this))"></span>
    </span>
    <div class="data">
        <div class="detailsRow">
            <span class="userProfile">
                <span class="name editableTxt" tabindex="-1" title=""><%=((transaction.alias && transaction.alias.name)?transaction.alias.name:"unnamed")%></span>
                <span class="bitprofileIcon" title="<%=(transaction.alias && transaction.alias.bitprofile)?'on':'no'%> bitprofile"></span>
            </span>
            <span class="detail s_titled hash" title="<%=transaction.hash%>"><%=shortify(transaction.hash, 20)%></span>
            <span class="detail txtBalance">
                <span class="int"><%=transaction.amount.int%></span><span class="dec"><%=transaction.amount.dec%></span>
            </span>
        </div>
        <div class="detailsRow">
            <span class="address"><%=(transaction.type=="received")?transaction.to:transaction.from%></span><span class="detail time" title="<%=transaction.time%>"><%=$.timeago(transaction.time)%></span>
        </div>
    </div>
</div>
<%}%>
