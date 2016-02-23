<%if(transaction.category=="Mined"){%>
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
            <span class="detail time"><%=$.timeago(transaction.timestamp)%></span>
        </div>
    </div>
</div>
<%}else{%>
<div class="listItem <%=((""+transaction.category).toLowerCase())%>" <%if(transaction.contact){%>contact="true"<%}%> style="display: block;">
    <div class="header icon">
        <span class="detail s_titled userAddress"><%=(transaction.category=="Received")?transaction.to:transaction.from%></span>
    </div>
    <span class="avatar">
        <span class="img"><img src="<%=(transaction.contact && transaction.contact.avatar)?transaction.contact.avatar:'img/avatarEmpty.png'%>" onerror="errorAvatar($(this))"></span>
    </span>
    <div class="data">
        <div class="detailsRow">
            <span class="userProfile">
                <span class="name editableTxt" tabindex="-1" title=""><%=((transaction.contact && transaction.contact.alias)?transaction.contact.alias:"unnamed")%></span>
                <span class="bitprofileIcon" title="<%=(transaction.contact && transaction.contact.bitprofile)?'on':'no'%> bitprofile"></span>
            </span>
            <span class="detail s_titled hash" title="<%=transaction.hash%>"><%=shortify(transaction.hash, 20)%></span>
            <span class="detail txtBalance">
                <span class="int"><%=transaction.amount.int%></span><span class="dec"><%=transaction.amount.dec%></span>
            </span>
        </div>
        <div class="detailsRow">
            <span class="address"><%=(transaction.category=="Received")?transaction.from:transaction.to%></span><span class="detail time"><%=$.timeago(transaction.timestamp)%></span>
        </div>
    </div>
</div>
<%}%>
