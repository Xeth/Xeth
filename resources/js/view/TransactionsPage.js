var TransactionView = Backbone.View.extend({
    initialize:function(options){
        _(this).bindAll("setTimeago", "copyHashToClipboard","updateAlias", "updateBitProfile", "clearContact", "changeContact", "updateAvatar","redirectSend", "redirectReceive");
        this.clipboard = options.clipboard;
        this.router = options.router;
        var data = this.model.toJSON();
        data.amount = splitAmount(data.amount);
        this.$el = $(options.template({transaction:data}));
        
        this.$el.tooltip({
            position: { my: "center bottom", at: "center top-5" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
        
        this.$el.find(".hash").click(this.copyHashToClipboard);
        
        this.$el.find(".hash").tooltip({
            position: { my: "center bottom-5", at: "center top" },
            track: true,
            show: { duration: 200 },
            hide: { duration: 200 }
        });
        
        this.bitprofileIcon = this.$el.find(".bitprofileIcon");
        this.aliasHolder = this.$el.find(".name");
        var contact = this.model.contact;
        if(contact) this.watchContact(contact);
        this.model.on("change:contact", this.changeContact);
        setTimeout(this.setTimeago, 50);
        this.$el.find(".data .address a").click(this.redirectSend);
        this.$el.find(".header .userAddress a").click(this.redirectReceive);
    },

    watchContact:function(contact){
        this.contact = contact;
        this.listenTo(contact, "change:alias", this.updateAlias);
        this.listenTo(contact, "change:bitprofile", this.updateBitProfile);
        this.listenTo(contact, "change:avatar", this.updateAvatar);
        this.listenTo(contact, "destroy", this.clearContact);
    },

    setTimeago:function(){
        this.time = this.$el.find('.detail.time');
        this.time.attr("title",this.time.text());
        this.time.timeago();
        this.time.tooltip({ 
            position: { my: "right bottom", at: "right+5 top-5" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
    },
    
    copyHashToClipboard:function(){
        if(this.clipboard.setText(this.model.get("hash")))
        {
            notifySuccess("hash copied to clipboard");
        }
        else
        {
            notifyError("failed to copy hash");
        }
    },

    updateAlias:function(contact, alias){
        this.aliasHolder.html(alias);
    },

    updateBitProfile: function(contact, bitprofile){

        if(bitprofile){
            if(!this.bitprofileIcon.hasClass("on")) this.bitprofileIcon.addClass("on");
            this.bitprofileIcon.attr("title", bitprofile);
        }else{
            this.bitprofileIcon.removeClass("on");
            this.bitprofileIcon.attr("title", "");
        }
    },

    updateAvatar:function(contact, avatar){
        var avatarHolder = this.$el.find(".avatar");
        if(!avatar){
            avatarHolder.remove();
        }
        else{
            if(avatarHolder.length){
                avatarHolder.find("img").attr("src", avatar);
            }else{
                $('<span class="avatar"><span class="img"><img src="'+avatar+'" onerror="errorAvatar($(this))"></span></span>').insertAfter(this.$el.find(".header"));
            }
        }
    },

    clearContact:function(contact){
        this.stopListening(contact);
        this.bitprofileIcon.removeClass("on");
        this.bitprofileIcon.attr("title", "");
        this.aliasHolder.html("unnamed");
        this.$el.find(".avatar").remove();
    },

    changeContact:function(contact){
        if(contact){
            this.watchContact(contact);
            this.updateAlias(contact, contact.get("alias"));
            this.updateBitProfile(contact, contact.get("bitprofile"));
            this.updateAvatar(contact, contact.get("avatar"));
        }
    },
    redirectSend:function(){
        this.router.redirect("send", {destination: (this.model.get("category") == "Sent")?this.model.get("stealth")||this.model.get("to"):this.model.get("from")});
    },
    redirectReceive:function(){
        this.router.redirect("receive", {address: (this.model.get("category") == "Sent")?this.model.get("from"):this.model.get("stealth")||this.model.get("to")});
    }
});


function TransactionViewFactory(template, clipboard, router){

    this.create = function(model){
        return new TransactionView({model:model, template:template, clipboard:clipboard, router:router});
    }
    return this;
}


var TransactionsPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("setTimeFilter", "setAddressFilter", "setTypeFilter", "applyFilters", "computeTotals", "processNewTransaction", "removeTransaction", "matchFilter");
        SubPageView.prototype.initialize.call(this,options);
        this.totalSent = 0;
        this.totalReceived = 0;
        this.template = options.templates.get("transactions");
        this.$el.html(this.template());
        this.accounts = options.accounts;
        this.filters = {timeStart:null, timeEnd:null, address:null, type:null};
        this.factory = new TransactionViewFactory(options.templates.get("transaction_item"), options.clipboard, options.router);
        this.collection = new CollectionView({
            collection:options.transactions,
            factory:this.factory,
            reversed:false,
            ordered:true,
            scroll: {scrollPage: this.$el.find(".scrollpage")/*, step: 106*/},
            el:this.$el.find(".transactionList"),
            empty:this.$el.find(".empty")
        });

        this.$sent = this.$el.find(".transactions_total .sent .txtBalance");
        this.$received = this.$el.find(".transactions_total .received .txtBalance");

        var dateInput = this.$el.find('.daterange');
        dateInput.daterangepicker({
            "showDropdowns": true, 
            "autoApply": true, 
            "startDate": "2015-11-01", 
            "endDate": moment(), 
            "opens": "left",
            locale: {format: 'YYYY-MM-DD'},
            ranges: {
               'All Time': ["2015-11-01", moment()],
               'Today': [moment(), moment()],
               'Yesterday': [moment().subtract(1, 'days'), moment().subtract(1, 'days')],
               'Last 7 Days': [moment().subtract(6, 'days'), moment()],
               'Last 30 Days': [moment().subtract(29, 'days'), moment()],
               'This Month': [moment().startOf('month'), moment().endOf('month')],
               'Last Month': [moment().subtract(1, 'month').startOf('month'), moment().subtract(1, 'month').endOf('month')]
            }
        }, this.setTimeFilter);
        dateInput.on('change.daterangepicker', function(ev, picker) {
            if(picker)
                $(this).val(picker.chosenLabel);
            else
                $(this).val("All Time");
        }).trigger('change.daterangepicker');

        this.typeFilter = this.$el.find("#filterTransactionType");
        this.typeFilter.selectmenu();
        this.typeFilter.on("selectmenuchange",this.setTypeFilter);
        
        this.listenTo(this.accounts, "change", this.setAddressFilter);
        this.listenTo(this.collection, "add", this.processNewTransaction);
        this.listenTo(this.collection, "remove", this.removeTransaction);
        this.listenTo(this.collection, "reset", this.computeTotals);
        this.computeTotals();
    },

    render:function(options){
        this.accounts.resize(21);
        this.accounts.compact(true);
        this.accounts.attach(this.$el.find("#filterTransactionAddress"));
        this.accounts.filter(function(){return true;}); //show all rows
        this.accounts.style("mini");
        if(options && options.focusFirst) this.collection.focusFirst();
    },

    setTimeFilter:function(start, end, label){
        if(label=='All Time'){
            this.filters.timeStart = this.filters.timeEnd = null
        }else{
            this.filters.timeStart = start;
            this.filters.timeEnd = end;
        }
        this.applyFilters();
    },

    setTypeFilter:function(ev){
        var type = (!ev.target)? ev : $(ev.target).val();
        this.filters.type = type=="All"?null:type;
        this.applyFilters();
    },

    setAddressFilter:function(model){
        var address = !model ? null : model.get("address")||model.get("stealth");
        this.filters.address = address;
        this.applyFilters();
    },

    applyFilters:function(){
        this.collection.filter(this.matchFilter);
        this.computeTotals();
    },

    matchFilter:function(model){
        var filters = this.filters;
        if(filters.timeStart&&filters.timeEnd){
            var time = model.get("timestamp");
            if(time<filters.timeStart||time>filters.timeEnd) return false;
        }
        if(filters.address && filters.address != model.get("from") && filters.address != model.get("to") && (filters.address!=model.get("stealth"))) return false;
        if(filters.type && filters.type!=model.get("category")) return false;
        return true;
    },

    computeTotals: function(){
        var sent = 0;
        var received = 0;
        this.collection.each(function(view){
            if(view.$el.is(":hidden")) return;
            var model = view.model;
            if(model.get("category")=="Sent")
                sent += model.get("amount");
            else
                received += model.get("amount"); //including mined
        });
        this.totalSent = sent;
        this.totalReceived = received;
        this.renderTotals();
    },

    processNewTransaction: function(view){
        var model = view.model;
        if(!this.matchFilter(model))
        {
            view.$el.hide();
        }
        else
        {
            view.$el.show();
            if(model.get("type")=="Sent")
                this.totalSent += model.get("amount");
            else
                this.totalReceived += model.get("amount"); //including mined
            this.renderTotals();
        }
    },

    removeTransaction:function(view){
        if(view.$el.is(":hidden")) return;
        var model = view.model;
        if(model.get("type")=="Sent")
            this.totalSent -= model.get("amount");
        else
            this.totalReceived -= model.get("amount"); //including mined
        this.renderTotals();
    },

    renderTotals:function(){
        var sent = splitAmount(this.totalSent);
        var received = splitAmount(this.totalReceived);
        this.$sent.find(".int").html(sent.int);
        this.$sent.find(".dec").html(sent.dec);
        this.$received.find(".int").html(received.int);
        this.$received.find(".dec").html(received.dec);
    }
});
