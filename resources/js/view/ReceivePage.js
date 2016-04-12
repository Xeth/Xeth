var ReceivePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "update", "scheduleUpdate", "copyAddressToClipboard", "copyUriToClipboard", "clickGenerate");
		SubPageView.prototype.initialize.call(this,options);
        this.clipboard = options.clipboard;
        this.router = options.router;
        this.template = options.templates.get("receive");
                
        this.accounts = new AccountSelect({collection:options.accounts, templates:options.templates});
        this.accounts.filter(function(model){return model!=undefined;}); //hide text
    },
    
    render:function(){
        this.$el.html(this.template());
        this.msg = this.$el.find("#receiveMessage");
        this.amount = this.$el.find("#receiveAmount");
        this.uri = this.$el.find(".txtURI");
        
        this.qr = new QRCode(this.$el.find("#receiveQR").get(0), {
            width : 240,
            height : 240,
            colorDark: "#1C2E30",
            colorLight: "rgba(255,255,255,0)",
            correctLevel : QRCode.CorrectLevel.M
        });

        this.msg.on("input",this.scheduleUpdate);
        this.amount.on("input", this.scheduleUpdate);
        this.msg.on("change",this.scheduleUpdate);
        this.amount.on("change",this.scheduleUpdate);

        this.$el.find("#copyReceiveURI").click(this.copyUriToClipboard);
        this.$el.find("#copyReceiveAddress").click(this.copyAddressToClipboard);
        this.$el.find("a.generate").click(this.clickGenerate);
        
        this.accounts.style("receive");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
        this.accounts.attach(this.$el.find("#receiveTo"));
        this.accounts.on("change", this.update);
    },
    
    exit:function(){
        //this.accounts.off("change", this.scheduleUpdate);
        this.stopUpdate();
        this.timer = true;
    },

    open:function(args){

        if(args&&args.address){
            this.accounts.focus(function(model){return model&&((model.get("address")==args.address)||(model.get("stealth")==args.address));})
        }
        
        (this.timer)?this.scheduleUpdate():this.update();
    },
    
    clickGenerate:function(){
        this.router.redirect("generate");
    },

    update:function(){
        this.stopUpdate();
        var uri = this.getURI();
        this.uri.html(uri);
        this.qr.makeCode(uri);
    },

    scheduleUpdate:function(){
        this.stopUpdate();
        this.timer = setTimeout(this.update, 1000);
    },

    stopUpdate:function(){
        clearTimeout(this.timer);
    },

    getSelectedAddress:function(){
        var account = this.accounts.selected();
        return account? account.get("address")||account.get("stealth") : "";
    },

    getURI:function(){
        var uri = "ethereum:"+this.getSelectedAddress();
        var msg = this.msg.val();
        var amount = this.amount.val();
        var attrs = [];
        if(amount){
            attrs.push("amount="+amount);
        }
        if(msg){
            attrs.push("message="+msg);
        }
        if(attrs.length){
            uri+="?"+attrs.join("&");
        }
        return uri;
    },

    copyAddressToClipboard:function(){
        this.clipboard.setText(this.getSelectedAddress());
        notifySuccess("address copied");
    },

    copyUriToClipboard:function(){
        this.clipboard.setText(this.getURI());
        notifySuccess("uri copied");
    }

})
