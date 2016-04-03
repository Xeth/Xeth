var ReceivePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("update", "scheduleUpdate", "copyAddressToClipboard", "copyUriToClipboard");
		SubPageView.prototype.initialize.call(this,options);
        this.accounts = options.accounts;
        this.clipboard = options.clipboard;
        this.template = options.templates.get("receive");
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
        this.$el.find("a.generate").click(function(){
            console.log("clicked on generate");
            options.router.redirect("generate");
        })
    },
    
    exit:function(){
        this.accounts.off("change", this.scheduleUpdate);
        this.stopUpdate();
        this.timer = true;
    },

    render:function(args){
        this.accounts.style("receive");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
        this.accounts.attach(this.$el.find("#receiveTo"));
        this.accounts.filter(function(model){return model!=undefined;}); //hide text
        if(args&&args.address){
            this.accounts.focus(function(model){ return (model.get("address")||model.get("stealth"))==args.address;})
        }
        this.accounts.on("change", this.scheduleUpdate);
        (this.timer)?this.scheduleUpdate():this.update();
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
