

<%if(transaction.category=="Mined"){%>
<div class="listItem off mined">
    <div class="header icon">
        <span class="detail s_titled userAddress"><%=transaction.to%></span>
    </div>
    <div class="data">
        <div class="detailsRow">
            <span class="detail s_titled hash" title="<%=transaction.hash%>"><%=shortify(transaction.hash, 45)%></span>
            <span class="detail txtBalance">
                <span class="int"><%=transaction.amount.int%></span><span class="dec"><%=transaction.amount.dec%></span>
            </span>
        </div>
        <div class="detailsRow">
            <span class="detail time"><%=moment(transaction.timestamp).format('YYYY-MM-DD HH:mm:ss')%></span>
        </div>
    </div>
</div>
<%}else{%>
<div class="listItem off <%=((""+transaction.category).toLowerCase())%>" <%if(transaction.contact){%>contact="true"<%}%>>
    <div class="header icon">
        <span class="detail s_titled userAddress"><%=((transaction.category=="Sent")?transaction.from:transaction.to)%></span>
    </div>
	<%if(transaction.contact && transaction.contact.avatar){%>
    <span class="avatar">
        <span class="img"><img src="<%=transaction.contact.avatar%>" onerror="errorAvatar($(this))"></span>
    </span>
	<%}%>
    <div class="data">
        <div class="detailsRow">
            <span class="userProfile">
                <span class="name editableTxt" tabindex="-1" title=""><%=((transaction.contact && transaction.contact.alias)?transaction.contact.alias:"unnamed")%></span>
                <span class="bitprofileIcon<%if(transaction.contact && transaction.contact.bitprofile){%> on<%}%>" title="<%=(transaction.contact && transaction.contact.bitprofile)?transaction.contact.bitprofile:'no bitprofile'%>"></span>
            </span>
            <span class="detail s_titled hash" title="<%=transaction.hash%>"><%=shortify(transaction.hash, 20)%></span>
            <span class="detail txtBalance">
                <span class="int"><%=transaction.amount.int%></span><span class="dec"><%=transaction.amount.dec%></span>
            </span>
        </div>
        <div class="detailsRow">
            <span class="address"><%=((transaction.category=="Sent")?transaction.to:transaction.from)%></span><span class="detail time"><%=moment(transaction.timestamp).format('YYYY-MM-DD HH:mm:ss')%></span>
        </div>
    </div>
</div>
<%}%>


