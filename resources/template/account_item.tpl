<%if(typeof address =="undefined"){%>
<li stealth="true">
    <a title="<%=stealth%>">
        <%if(typeof bitprofile!="undefined"){%>
        <span class="account bitprofile">
            <span class="id"><%=bitprofile%></span>
        <%}else{bitprofile = ""; %>
        <span class="account stealth">
        <%}%>
            <span class="shortAddress"><%=shortify(stealth, 57-bitprofile.length*0.8)%></span>
        </span>
    </a>
</li>
<%}else{%>
<li>
    <a title="<%=address%>">
        <span class="amount txtBalance">
            <span class="int"><%=parseInt(balance)%></span><span class="dec"><%=parseDecimals(balance)%></span>
        </span>
        <%if(typeof bitprofile!="undefined"){%>
        <span class="account originated originBitprofile">
            <span class="address"><%=address%></span>
            <span class="origin bitprofile">
                <span class="id"><%=bitprofile%></span>
                <%if(typeof stealth!="undefined"){%>
                <span class="address"><%=shortify(stealth, 67-bitprofile.length)%></span>
                <%}%>
            </span>
        </span>
        <%}else if(typeof stealth!="undefined"){%>
        <span class="account originated originStealth">
            <span class="address"><%=address%></span>
            <span class="origin stealth"><span class="address"><%=shortify(stealth)%></span></span>
        </span>
        <%}else{%>
        <span class="account"><span class="address"><%=address%></span></span>
        <%}%>
    </a>
</li>
<%}%>
