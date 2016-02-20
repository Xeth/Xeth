<%if(!account.address){%>
<div class="item" stealth="true">
    <a title="<%=account.stealth%>">
        <%if(account.bitprofile){%>
        <span class="account bitprofile">
            <span class="id"><%=account.bitprofile%></span>
        <%}else{%>
        <span class="account stealth">
        <%}%>
            <span class="address"><%=shortify(account.stealth, width-(""+account.bitprofile).length)%></span>
        </span>
    </a>
</div>
<%}else{%>
<div class ="item">
    <a title="<%=account.address%>">
        <span class="amount txtBalance">
            <span class="int"><%=account.balance.int%></span><span class="dec"><%=account.balance.dec%></span>
        </span>
        <%if(account.bitprofile){%>
        <span class="account originated originBitprofile">
            <span class="address"><%=account.address%></span>
            <span class="origin bitprofile">
                <span class="id"><%=account.bitprofile%></span>
                <%if(account.stealth){%>
                <span class="address"><%=shortify(account.stealth, width-account.bitprofile.length)%></span>
                <%}%>
            </span>
        </span>
        <%}else if(account.stealth){%>
        <span class="account originated originStealth">
            <span class="address"><%=account.address%></span>
            <span class="origin stealth"><span class="address"><%=shortify(account.stealth, width)%></span></span>
        </span>
        <%}else{%>
        <span class="account"><span class="address"><%=account.address%></span></span>
        <%}%>
    </a>
</div>
<%}%>
