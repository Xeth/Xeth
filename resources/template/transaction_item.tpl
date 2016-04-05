

<%if(transaction.category=="Mined"){%>
<div class="listItem new mined">
    <div class="header icon">
        <span class="detail s_titled userAddress"><a href="javascript:void(0)"><%=transaction.to%></a></span>
    </div>
    <div class="data">
        <div class="detailsRow">
            <a class="detail s_titled hash" title="copy hash"><%=shortify(transaction.hash, 45)%></a>
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
<div class="listItem new <%=((""+transaction.category).toLowerCase())%>" <%if(transaction.contact){%>contact="true"<%}%>>
    <div class="header icon">
        <span class="detail s_titled userAddress">
            <%if(transaction.category=="Sent"){%>
                <a href="javascript:void(0)"><%=transaction.from%></a>
            <%}else{%>
                <%if(transaction.stealth){%><span class="stealthIcon" title="<%=transaction.stealth%>"></span><%}%>
                <a href="javascript:void(0)"><%=transaction.to%></a>
            <%}%>
        </span>
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
            <a class="detail s_titled hash" title="copy hash"><%=shortify(transaction.hash, 20)%></a>
            <span class="detail txtBalance">
                <span class="int"><%=transaction.amount.int%></span><span class="dec"><%=transaction.amount.dec%></span>
            </span>
        </div>
        <div class="detailsRow">
            <span class="address">
                <%if(transaction.category=="Sent"){%>
                    <%if(transaction.stealth){%><span class="stealthIcon" title="<%=transaction.stealth%>"></span><%}%>
                    <a href="javascript:void(0)"><%=transaction.to%></a>
                <%}else{%>
                    <a href="javascript:void(0)"><%=transaction.from%></a>
                <%}%>
            </span>
            <span class="detail time"><%=moment(transaction.timestamp).format('YYYY-MM-DD HH:mm:ss')%></span>
        </div>
    </div>
</div>
<%}%>


